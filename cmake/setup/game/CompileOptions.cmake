if(CMAKE_GENERATOR MATCHES "^(Visual Studio)")
    target_compile_options(nimbus_game INTERFACE /MP)
endif()


if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang|IntelLLVM|AppleClang")
    target_compile_options(nimbus_game PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_compile_options(nimbus_game PRIVATE
            /W4 /WX
    )
endif()
