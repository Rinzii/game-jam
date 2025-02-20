
#pragma once

// Use this for reference: https://en.cppreference.com/w/cpp/compiler_support

#include "nimbus/core/common/Compiler.hpp"


// https://learn.microsoft.com/en-us/cpp/intrinsics/compiler-intrinsics?view=msvc-170
// https://clang.llvm.org/docs/LanguageExtensions.html
// https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gcc/X86-Built-in-Functions.html

#if defined(__cplusplus) && __cplusplus >= 202302L
  #define NIM_COMPILER_CPP23_ENABLED
#endif

// ------------------------------------------------------------------------
// NIM_STRINGIFY
//
// Example usage:
//     printf("Line: %s", NIM_STRINGIFY(__LINE__));
//
#ifndef NIM_STRINGIFY
#define NIM_STRINGIFY(x) NIM_STRINGIFY_IMPL(x)
#define NIM_STRINGIFY_IMPL(x) #x
#endif

// https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html
// https://clang.llvm.org/docs/UsersManual.html#controlling-diagnostics-via-pragmas
#ifndef NIM_WARNING
#if defined(NIM_COMPILER_CLANG) || defined(NIM_COMPILER_GCC)
#define NIM_WARNING(msg) _Pragma(NIM_STRINGIFY(GCC warning msg)
#else
#define NIM_WARNING(msg)
#endif
#endif

#ifndef NIM_FORCE_INLINE
#ifndef CONFIG_NIM_DISABLE_FORCED_INLINING
#if defined(NIM_COMPILER_MSVC)
#define NIM_FORCE_INLINE __forceinline
#elif defined(NIM_COMPILER_GCC) && (((__GNUC__ * 100) + __GNUC_MINOR__) >= 301) || defined(NIM_COMPILER_CLANG)
#if defined(__cplusplus)
#define NIM_FORCE_INLINE inline __attribute__((always_inline))
#else
#define NIM_FORCE_INLINE __inline__ __attribute__((always_inline))
#endif
#else
#if defined(__cplusplus)
#define NIM_FORCE_INLINE inline
#else
#define NIM_FORCE_INLINE __inline
#endif
#endif
#else // If CONFIG_NIM_DISABLE_FORCED_INLINING is defined then don't force inlining
#if defined(__cplusplus)
			#define NIM_FORCE_INLINE inline
		#else
			#define NIM_FORCE_INLINE __inline
		#endif
#endif
#endif

#ifndef NIM_NOINLINE
#if defined(NIM_COMPILER_MSVC)
#define NIM_NOINLINE __declspec(noinline)
#elif defined(NIM_COMPILER_GCC) || defined(NIM_COMPILER_CLANG)
#define NIM_NOINLINE __attribute__((noinline))
#else
#define NIM_NOINLINE
#endif
#endif


#ifndef NIM_ASSUME
#if defined(NIM_COMPILER_CPP23_ENABLED)// This is a dummy define for when c++23 is finalized.
#define NIM_ASSUME(expr) [[assume(expr)]]
#elif defined(NIM_COMPILER_GCC) && (__GNUC__ >= 13) // Currently only GCC supports assume
#define NIM_ASSUME(expr) [[assume(expr)]]
#elif defined(NIM_COMPILER_MSVC)
#define NIM_ASSUME(expr) __assume(expr)
#elif defined(NIM_COMPILER_CLANG) && (__clang_major__ >= 4)
#define NIM_ASSUME(expr) __builtin_assume(expr)
#elif defined(NIM_COMPILER_GCC) && ((__GNUC__ >= 12) && (__GNUC_MINOR__ >= 1))
#define NIM_ASSUME(expr) __attribute__((assume(expr)))
#else
#define NIM_ASSUME(expr)
#endif
#endif


#ifndef NIM_LIKELY_EXPR
#if defined(NIM_COMPILER_GCC) || defined(NIM_COMPILER_CLANG)
#define NIM_LIKELY_EXPR(expr) __builtin_expect(!!(expr), 1)
#else
#define NIM_LIKELY_EXPR(expr) (expr)
#endif
#endif


#if defined(NIM_COMPILER_MSVC)
#define NIM_PRAGMA(x) __pragma(x)
#else
#define NIM_PRAGMA(x) _Pragma(#x)
#endif
