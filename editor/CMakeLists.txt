if (NOT DEFINED NIMBUS_ROOT_DIR)
    message(FATAL_ERROR "NIMBUS_ROOT_DIR has not been specified! Did you some how call the editor target without nimbus?")
endif ()

project(editor)

add_executable(editor)
set_target_properties(editor PROPERTIES OUTPUT_NAME "editor")
target_link_libraries(editor PRIVATE
        nimbus::lib
)

target_include_directories(editor
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)

# Setup Includes
include(${NIMBUS_ROOT_DIR}/cmake/setup/engine/CompilerOptions.cmake)


add_subdirectory(include/editor)
add_subdirectory(src)
