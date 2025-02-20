# User configurable options

option(NIMBUS_BUILD_EDITOR "Build the editor." OFF)
message(STATUS "NIMBUS_BUILD_EDITOR         : ${NIMBUS_BUILD_EDITOR}")

option(NIMBUS_BUILD_GAME "Build the game." ON)
message(STATUS "NIMBUS_BUILD_GAME           : ${NIMBUS_BUILD_GAME}")

option(NIMBUS_BUILD_LAUNCHER "Build the launcher." ON)
message(STATUS "NIMBUS_BUILD_LAUNCHER       : ${NIMBUS_BUILD_LAUNCHER}")

if (NIMBUS_BUILD_LAUNCHER AND NOT NIMBUS_BUILD_GAME)
    message(FATAL_ERROR "NIMBUS_BUILD_LAUNCHER is enabled but NIMBUS_BUILD_GAME is disabled! This is not allowed as the launcher has an intrinsic dependency on the game!")
endif ()