project(rpmalloc VERSION 1.4.5)

# Add the rpmalloc library target
add_library(rpmalloc)
add_library(rpmalloc::rpmalloc ALIAS rpmalloc)

target_include_directories(rpmalloc SYSTEM PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(rpmalloc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/rpmalloc.c
)