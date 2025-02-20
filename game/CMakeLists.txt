if (NOT DEFINED NIMBUS_ROOT_DIR)
  message(FATAL_ERROR "NIMBUS_ROOT_DIR has not been specified! Did you some how call the game target without nimbus?")
endif ()

project(nimbus_game LANGUAGES CXX VERSION 0.0.1)

add_library(nimbus_game)
add_library(nimbus::game ALIAS nimbus_game)

target_link_libraries(nimbus_game
        PRIVATE
        nimbus::lib
)

# Setup our include structure
target_include_directories(nimbus_game
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)

# Setup Includes
include(${NIMBUS_ROOT_DIR}/cmake/setup/game/CompileOptions.cmake)
include(${NIMBUS_ROOT_DIR}/cmake/setup/game/CompileDefinitions.cmake)



add_subdirectory(include/game)
add_subdirectory(src)
