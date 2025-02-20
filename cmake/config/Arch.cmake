# detect the architecture (note: this test won't work for cross-compilation)
if("${CMAKE_GENERATOR_PLATFORM}" MATCHES "ARM64" OR "${MSVC_CXX_ARCHITECTURE_ID}" MATCHES "ARM64" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "ARM64")
    set(ARCH_ARM64 1)
    message(STATUS "Nimbus - Detected Arch      : ARM64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(NIMBUS_ARCH_X64 1)
    message(STATUS "Nimbus - Detected Arch      : X64")

elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(NIMBUS_ARCH_X86 1)
    message(STATUS "Nimbus - Detected Arch      : X86")

elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^armv7")
    set(NIMBUS_ARCH_ARM 1)
    message(STATUS "Nimbus - Detected Arch      : ARM")

elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
    set(NIMBUS_ARCH_ARM64 1)
    message(STATUS "Nimbus - Detected Arch      : ARM64")

else()
    message(FATAL_ERROR "Unsupported architecture")
    return()
endif()

