# User configurable options

option(NIMBUS_BUILD_EDITOR "Build the editor." OFF)
message(STATUS "NIMBUS_BUILD_EDITOR         : ${NIMBUS_BUILD_EDITOR}")
if (NIMBUS_BUILD_EDITOR AND DEFINED NIMBUS_PRODUCTION_BUILD)
    message(FATAL_ERROR "NIMBUS_BUILD_EDITOR is enabled but NIMBUS_PRODUCTION_BUILD is enabled! This is not allowed as the editor should not be built in production builds!")
endif ()

option(NIMBUS_BUILD_GAME "Build the game." ON)
message(STATUS "NIMBUS_BUILD_GAME           : ${NIMBUS_BUILD_GAME}")

option(NIMBUS_BUILD_LAUNCHER "Build the launcher." ON)
message(STATUS "NIMBUS_BUILD_LAUNCHER       : ${NIMBUS_BUILD_LAUNCHER}")
if (NIMBUS_BUILD_LAUNCHER AND NOT NIMBUS_BUILD_GAME)
    message(FATAL_ERROR "NIMBUS_BUILD_LAUNCHER is enabled but NIMBUS_BUILD_GAME is disabled! This is not allowed as the launcher has an intrinsic dependency on the game!")
endif ()

option(NIMBUS_ENABLE_PROFILER "Enable the profiler." OFF)
message(STATUS "NIMBUS_ENABLE_PROFILER      : ${NIMBUS_ENABLE_PROFILER}")
if (NIMBUS_ENABLE_PROFILER AND DEFINED NIMBUS_PRODUCTION_BUILD)
    message(FATAL_ERROR "NIMBUS_ENABLE_PROFILER is enabled but NIMBUS_PRODUCTION_BUILD is enabled! This is not allowed as the profiler should not be enabled in production builds!")
endif ()

if (DEFINED NIMBUS_PRODUCTION_BUILD)
    message(STATUS "NIMBUS_PRODUCTION_BUILD     : Defined")
endif ()