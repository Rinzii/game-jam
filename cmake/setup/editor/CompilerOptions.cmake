if(CMAKE_GENERATOR MATCHES "^(Visual Studio)")
    target_compile_options(nimbus_editor INTERFACE /MP)
endif()


if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang|IntelLLVM|AppleClang")
    target_compile_options(nimbus_editor PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_compile_options(nimbus_editor PRIVATE
            /W4 /WX
    )
endif()

if (WIN32)
    # disable deprecation warnings
    target_compile_definitions(nimbus_editor PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()