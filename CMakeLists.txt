
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED FORNANI_ROOT_DIR)
    set(FORNANI_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Fornani root directory")
endif ()

project(fornani
        LANGUAGES CXX
        VERSION 1.0
)

option(FORNANI_PRODUCTION_BUILD "If enabled, will build the game in production mode" OFF)
option(FORNANI_BUILD_EDITOR "Build the editor. This should never be enabled in production!" ON)
option(FORNANI_ENABLE_PROFILER "Enables tracy profiling. This should never be enabled in production!" OFF)
option(
        FORNANI_ENABLE_VERBOSE_LOGGING
        "Enable verbose logging that will output source location information.
        You should only have this enabled if you are debugging!
        This should never be enabled in production!"
        OFF
)

include(cmake/helpers/OptionMessages.cmake)

include(cmake/func/AddTargetSource.cmake)
include(cmake/GenerateDataTemplates.cmake)

add_subdirectory(dependencies)
add_subdirectory(game)
if (FORNANI_BUILD_EDITOR AND NOT DEFINED FORNANI_ENABLE_PRODUCTION_BUILD)
    add_subdirectory(editor)
endif ()
add_subdirectory(launcher)


if (FORNANI_ENABLE_PROFILER AND NOT DEFINED FORNANI_ENABLE_PRODUCTION_BUILD)
    target_compile_definitions(fornani PRIVATE TRACY_ENABLE)
    target_compile_definitions(fornani PRIVATE FORNANI_PROFILE)
endif ()

if (DEFINED FORNANI_DISABLE_DBGHELP)
    target_compile_definitions(fornani PRIVATE NANI_DISABLE_ADVANCED_CRASH_REPORTING)
endif ()

if (DEFINED FORNANI_ENABLE_PRODUCTION_BUILD)
    target_compile_definitions(fornani PRIVATE FORNANI_PRODUCTION)
endif ()