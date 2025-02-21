#pragma once

#include <vector>
#include <shared_mutex>
#include <atomic>
#include <memory>
#include <mutex>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <cstddef>
#include <new>

#include <rpmalloc.h>

// design based on Impossibly Fast Event:
// https://docs.google.com/presentation/d/1Y5JktAemPYNDmVJ5-3f_KQH1LTDmey-YJFAnly0Cxpo/edit?usp=sharing

// If you have questions about this, ask Ian.

namespace nim::core {
    namespace details {

        // Custom STL allocator using rpmalloc/rpfree.
        template<typename T>
        struct rpmalloc_allocator {
            using value_type = T;

            rpmalloc_allocator() noexcept = default;

            template<typename U>
            rpmalloc_allocator(const rpmalloc_allocator<U>&) noexcept {}

            T* allocate(std::size_t n) {
                if (n > static_cast<std::size_t>(-1) / sizeof(T))
                    throw std::bad_alloc();
                if (auto ptr = static_cast<T*>(rpmalloc(n * sizeof(T))))
                    return ptr;
                throw std::bad_alloc();
            }

            void deallocate(T* p, std::size_t) noexcept {
                rpfree(p);
            }

            template<typename U>
            bool operator==(const rpmalloc_allocator<U>&) const noexcept { return true; }
            template<typename U>
            bool operator!=(const rpmalloc_allocator<U>&) const noexcept { return false; }
        };

        struct ConnectionBase;

        struct EventBase {
            struct call {
                void *object;
                void *func;
            };

            // Use the custom allocator for both vectors.
            mutable std::vector<call, rpmalloc_allocator<call>> calls;
            mutable std::vector<ConnectionBase*, rpmalloc_allocator<ConnectionBase*>> connections;

            // We are able to optimize space by stealing 2 unused bits from our vector size.
            mutable bool calling = false;
            mutable bool dirty = false;

            EventBase() = default;
            ~EventBase();
            EventBase(const EventBase &) = delete;
            EventBase &operator=(const EventBase &) = delete;
            EventBase(EventBase &&other) noexcept;
            EventBase &operator=(EventBase &&other) noexcept;
        };

        struct BlockedConnection {
            const EventBase *sig = nullptr;
            EventBase::call call = { .object = nullptr, .func = nullptr };
        };

        struct ConnectionBase {
            union {
                const EventBase *event;
                BlockedConnection *blocked_conn;
            };

            size_t idx;
            // space can be optimized by stealing bits from index as it's impossible to support max uint64 number of slots
            bool blocked = false;
            bool owned = false;

            ConnectionBase(const EventBase *sig, size_t idx) : event(sig), idx(idx) { }

            virtual ~ConnectionBase() {
                if (!blocked) {
                    // NOLINTBEGIN
                    if (event) {
                        event->calls[idx].object = nullptr;
                        event->calls[idx].func = nullptr;
                        event->connections[idx] = nullptr;
                        event->dirty = true;
                    }
                    // NOLINTEND
                } else {
                    // If the connection is blocked, destroy and free the blocked connection storage.
                    blocked_conn->~BlockedConnection();
                    rpfree(blocked_conn);
                }
            }

            void set_event(const EventBase *sig) {
                // NOLINTBEGIN
                if (blocked) {
                    this->blocked_conn->sig = sig;
                } else {
                    this->event = sig;
                }
                // NOLINTEND
            }

            void block() {
                if (!blocked) {
                    blocked = true;
                    // NOLINTBEGIN
                    const EventBase *orig_sig = event;
                    event = nullptr;
                    // Allocate BlockedConnection via rpmalloc and use placement new.
                    blocked_conn = static_cast<BlockedConnection*>(rpmalloc(sizeof(BlockedConnection)));
                    new (blocked_conn) BlockedConnection();
                    blocked_conn->sig = orig_sig;
                    std::swap(blocked_conn->call, orig_sig->calls[idx]);
                    // NOLINTEND
                }
            }

            void unblock() {
                if (blocked) {
                    // NOLINTBEGIN
                    const EventBase *orig_sig = blocked_conn->sig;
                    std::swap(blocked_conn->call, orig_sig->calls[idx]);
                    // Manually call destructor and free the memory allocated for blocked_conn.
                    blocked_conn->~BlockedConnection();
                    rpfree(blocked_conn);
                    blocked_conn = nullptr;
                    event = orig_sig;
                    // NOLINTEND
                    blocked = false;
                }
            }

            // Override operator new/delete to use rpmalloc/rpfree for connection objects.
            void* operator new(size_t size) {
                return rpmalloc(size);
            }

            void operator delete(void* ptr) {
                rpfree(ptr);
            }
        };

        template<typename T>
        struct ConnectionNontrivial final : ConnectionBase {
            using ConnectionBase::ConnectionBase;

            ~ConnectionNontrivial() override {
                // NOLINTBEGIN
                if (event) {
                    reinterpret_cast<T *>(&event->calls[idx].object)->~T();
                }
                // NOLINTEND
            }
        };

        inline EventBase::~EventBase() {
            for (ConnectionBase *c : connections) {
                if (c != nullptr) {
                    if (c->owned) {
                        c->set_event(nullptr);
                    } else {
                        delete c;
                    }
                }
            }
        }

        inline EventBase::EventBase(EventBase &&other) noexcept
            : calls(std::move(other.calls))
              , connections(std::move(other.connections))
              , calling(other.calling)
              , dirty(other.dirty) {
            for (ConnectionBase *c : connections) {
                if (c != nullptr) {
                    c->set_event(this);
                }
            }
        }

        inline EventBase &EventBase::operator=(EventBase &&other) noexcept {
            calls = std::move(other.calls);
            connections = std::move(other.connections);
            calling = other.calling;
            dirty = other.dirty;
            for (ConnectionBase *c : connections) {
                if (c != nullptr) {
                    c->set_event(this);
                }
            }
            return *this;
        }
    } // namespace details

    template<typename F>
    struct Event;

    // A connection without auto disconnection.
    struct ConnectionRaw {
        details::ConnectionBase *ptr = nullptr;
    };

    struct Connection {
        details::ConnectionBase *ptr = nullptr;

        void disconnect() {
            delete ptr;
            ptr = nullptr;
        }

        void block() const { ptr->block(); }
        void unblock() const { ptr->unblock(); }

        Connection() = default;
        ~Connection() { disconnect(); }
        Connection(const Connection &) = delete;
        Connection &operator=(const Connection &) = delete;

        Connection(Connection &&other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
        Connection &operator=(Connection &&other) noexcept {
            disconnect();
            ptr = other.ptr;
            other.ptr = nullptr;
            return *this;
        }

        // TODO: This might not work with explicit. Verify later.
        explicit Connection(ConnectionRaw conn) : ptr(conn.ptr) { ptr->owned = true; }
    };

    template<typename... A>
    struct Event<void(A...)> : details::EventBase {
        template<typename... ActualArgsT>
        void operator()(ActualArgsT &&... args) const {
            const bool recursion = calling;
            if (!calling) {
                calling = true;
            }
            for (size_t i = 0, n = calls.size(); i < n; ++i) {
                auto &[object, func] = calls[i];
                if (func) {
                    if (object == func) {
                        reinterpret_cast<void(*)(A...)>(func)(std::forward<ActualArgsT>(args)...); // NOLINT
                    } else {
                        // NOLINTNEXTLINE
                        reinterpret_cast<void(*)(void *, A...)>(func)(&object, std::forward<ActualArgsT>(args)...);
                    }
                }
            }

            if (!recursion) {
                calling = false;
                if (dirty) {
                    dirty = false;
                    // remove all empty slots while patching the stored index in the connection
                    size_t sz = 0;
                    for (size_t i = 0, n = connections.size(); i < n; ++i) {
                        if (connections[i]) {
                            connections[sz] = connections[i];
                            calls[sz] = calls[i];
                            connections[sz]->idx = sz;
                            ++sz;
                        }
                    }
                    connections.resize(sz);
                    calls.resize(sz);
                }
            }
        }

        template<typename... ActualArgsT>
        void invoke(ActualArgsT &&... args) const {
            operator()(std::forward<ActualArgsT>(args)...);
        }

        template<auto PMF, class C>
        ConnectionRaw connect(C *object) const {
            size_t idx = connections.size();
            auto &call = calls.emplace_back();
            call.object = object;
            // NOLINTNEXTLINE
            call.func = reinterpret_cast<void *>(+[](void *obj, A... args) {
                ((*static_cast<C **>(obj))->*PMF)(args...);
            });
            auto *conn = new details::ConnectionBase(this, idx); // uses overridden operator new (rpmalloc)
            connections.emplace_back(conn);
            return {conn};
        }

        template<auto PMF, class C>
        ConnectionRaw operator+=(C *object) const {
            return connect<PMF, C>(object);
        }

        template<auto func>
        ConnectionRaw connect() const { return connect(func); }

        ConnectionRaw connect(void (*func)(A...)) const {
            size_t idx = connections.size();
            auto &call = calls.emplace_back();
            call.func = call.object = reinterpret_cast<void *>(func); // NOLINT
            auto *conn = new details::ConnectionBase(this, idx); // uses overridden operator new (rpmalloc)
            connections.emplace_back(conn);
            return {conn};
        }

        ConnectionRaw operator+=(void (*func)(A...)) const {
            return connect(func);
        }

        template<typename F>
        ConnectionRaw connect(F &&functor) const {
            using f_type = std::remove_pointer_t<std::remove_reference_t<F>>;
            if constexpr (std::is_convertible_v<f_type, void(*)(A...)>) {
                return connect(+functor);
            } else if constexpr (std::is_lvalue_reference_v<F>) {
                size_t idx = connections.size();
                auto &call = calls.emplace_back();
                // NOLINTNEXTLINE
                call.func = reinterpret_cast<void *>(+[](void *obj, A... args) {
                    (*static_cast<f_type **>(obj))->operator()(args...);
                });
                call.object = &functor;
                auto *conn = new details::ConnectionBase(this, idx); // uses overridden operator new (rpmalloc)
                connections.emplace_back(conn);
                return {conn};
            } else if constexpr (sizeof(std::remove_pointer_t<f_type>) <= sizeof(void *)) {
                // copy the functor.
                size_t idx = connections.size();
                auto &call = calls.emplace_back();
                // NOLINTNEXTLINE
                call.func = reinterpret_cast<void *>(+[](void *obj, A... args) {
                    static_cast<f_type *>(obj)->operator()(args...);
                });
                new(&call.object) f_type(std::forward<F>(functor));
                using conn_t = std::conditional_t<std::is_trivially_destructible_v<F>,
                    details::ConnectionBase,
                    details::ConnectionNontrivial<F>>;
                details::ConnectionBase *conn = new conn_t(this, idx); // uses overridden operator new (rpmalloc)
                connections.emplace_back(conn);
                return {conn};
            } else {
                struct unique {
                    f_type *ptr;
                    explicit unique(f_type *ptr) : ptr(ptr) {}
                    unique(const unique &) = delete;
                    unique(unique &&) = delete;
                    ~unique() { delete ptr; }
                };

                size_t idx = connections.size();
                auto &call = calls.emplace_back();
                // NOLINTNEXTLINE
                call.func = reinterpret_cast<void *>(+[](void *obj, A... args) {
                    static_cast<unique *>(obj)->ptr->operator()(args...);
                });
                new(&call.object) unique{new f_type(std::forward<F>(functor))};
                details::ConnectionBase *conn = new details::ConnectionNontrivial<unique>(this, idx); // uses overridden operator new (rpmalloc)
                connections.emplace_back(conn);
                return {conn};
            }
        }

        template<typename F>
        ConnectionRaw operator+=(F &&functor) const {
            return connect(std::forward<F>(functor));
        }
    };
} // namespace nim::core

/*
 * Example usage: https://godbolt.org/z/6vEd1eqcn
 */
