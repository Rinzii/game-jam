project(nimbus_deps)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

# SFML
FetchContent_Declare(sfml
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(sfml)

# rpmalloc
add_subdirectory(rpmalloc)

# Dear ImGui
add_subdirectory(imgui)

# Dear ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF)
add_subdirectory(imgui-sfml)

# djson
FetchContent_Declare(
        djson
        GIT_REPOSITORY https://github.com/karnkaul/djson
        GIT_TAG v2.1.1
)
FetchContent_MakeAvailable(djson)
#
## tracy
#FetchContent_Declare(
#        tracy
#        GIT_REPOSITORY https://github.com/wolfpld/tracy
#        GIT_TAG v0.11.1
#)
#FetchContent_MakeAvailable(tracy)

# ccmath
set(CCMATH_ENABLE_EXTENSIONS ON)
set(CCMATH_DISABLE_ERRNO ON)
set(CCMATH_STRICT_WARNINGS OFF)
FetchContent_Declare(
        ccmath
        GIT_REPOSITORY https://github.com/Rinzii/ccmath
        GIT_TAG 15260da # IanP: This specific commit id is stable but more recent than main
)
FetchContent_MakeAvailable(ccmath)

# Used for assertions and crash handling

FetchContent_Declare(
        cpptrace
        GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace
        GIT_TAG v0.7.5
)
FetchContent_MakeAvailable(cpptrace)

FetchContent_Declare(
        libassert
        GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert
        GIT_TAG v2.1.4
)
FetchContent_MakeAvailable(libassert)

add_library(nimbus_deps INTERFACE)
add_library(nimbus::deps ALIAS nimbus_deps)

target_link_libraries(nimbus_deps INTERFACE
        # TODO: Uncomment this all later once cmake is finished and we need specific deps.
        SFML::System
        SFML::Graphics
        SFML::Window
        SFML::Audio
        ImGui-SFML::ImGui-SFML
        rpmalloc::rpmalloc

        djson::djson
        ccmath::ccmath
        #Tracy::TracyClient
        cpptrace::cpptrace
        libassert::assert
)
