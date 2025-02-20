if (NOT DEFINED NIMBUS_ROOT_DIR)
    message(FATAL_ERROR "NIMBUS_ROOT_DIR has not been specified! Did you some how call the launcher target without nimbus?")
endif ()

project(nimbus_launcher)

add_executable(nimbus_launcher)
set_target_properties(nimbus_launcher PROPERTIES OUTPUT_NAME "game")
target_link_libraries(nimbus_launcher PRIVATE
        nimbus::game
        nimbus::lib
)

if(NIMBUS_BUILD_EDITOR)
    target_link_libraries(nimbus_launcher PRIVATE
            editor::lib
    )
endif()

target_include_directories(nimbus_launcher
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)

# Setup Includes
include(${NIMBUS_ROOT_DIR}/cmake/setup/launcher/CompileOptions.cmake)
include(${NIMBUS_ROOT_DIR}/cmake/setup/launcher/CompileDefinitions.cmake)


add_subdirectory(include/launcher)
add_subdirectory(src)

# TODO: Is this even needed anymore?
if (WIN32)
    if (MSVC)
        set(subsystem $<IF:$<BOOL:$<CONFIG:Debug>>,CONSOLE,WINDOWS>)
        target_link_options(nimbus_launcher PRIVATE
                /SUBSYSTEM:${subsystem}
                /ENTRY:mainCRTStartup
        )
    endif ()
endif ()
