if (NOT DEFINED NIMBUS_ROOT_DIR)
  message(FATAL_ERROR "NIMBUS_ROOT_DIR has not been specified! Did you some how call the engine target without nimbus?")
endif ()

add_library(nimbus)
add_library(nimbus::lib ALIAS nimbus)
set_target_properties(nimbus PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(nimbus
        PUBLIC
        $<$<CONFIG:Debug>:NIM_DEBUG>

        $<$<CONFIG:RelWithDebInfo>:NIM_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:NIM_RELEASE>

        $<$<CONFIG:Release>:NIM_NDEBUG>
        $<$<CONFIG:Release>:NIM_RELEASE>
)

target_link_libraries(nimbus
        PRIVATE
        nimbus::deps
)

# Setup our include structure
target_include_directories(nimbus
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)

# Setup Includes
include(${NIMBUS_ROOT_DIR}/cmake/setup/engine/CompileOptions.cmake)
include(${NIMBUS_ROOT_DIR}/cmake/setup/engine/CompileDefinitions.cmake)


add_subdirectory(include/nimbus)
add_subdirectory(src)
