
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")

project(nimbus
        LANGUAGES CXX
        VERSION 0.0.1
)

# Project setup
include(cmake/setup/project/DefineRootDirectories.cmake) # Sets all root directory variables.
include(cmake/setup/project/UserOptions.cmake)
include(cmake/func/AddTargetSource.cmake)

# Config
include(cmake/config/OS.cmake)
include(cmake/config/Arch.cmake)
include(cmake/config/Compiler.cmake)


# Add all of our other targets we will need
add_subdirectory(deps)
add_subdirectory(engine)
if (NIMBUS_BUILD_EDITOR)
    add_subdirectory(editor)
endif ()
if (NIMBUS_BUILD_GAME)
    add_subdirectory(game)
endif ()
if (NIMBUS_BUILD_LAUNCHER) # Launcher being enabled intrinsically includes game also
    add_subdirectory(launcher)
endif ()