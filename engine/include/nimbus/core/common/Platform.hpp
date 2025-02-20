
#pragma once

// NOLINTBEGIN

// TODO: Add platform detection for the nintendo switch
// TODO: Add platform detection for the xbox series x/s

// This script is a little crusty but it's very useful. Also the macros for console detection used here are public knowledge.


// Pretty confident this will cover all modern PSX platforms.
#if defined(NIM_PLATFORM_PS4) || defined(NIM_PLATFORM_PS5) || defined(__ORBIS__) || defined(__PROSPERO__) || defined(__SCE__)

#if defined(__ORBIS__)
    // Platform specific defines for PS4
    #undef NIM_PLATFORM_PS4
    #define NIM_PLATFORM_PS4 1
    #undef NIM_PLATFORM_ORBIS
    #define NIM_PLATFORM_ORBIS 1

    #define NIM_PLATFORM_NAME "PS4"
    #define NIM_PLATFORM_CONSOLE 1

    // Generic platform defines for PSX
    #define NIM_PLATFORM_SONY 1
    #define NIM_PLATFORM_POSIX 1

#elif defined(__PROSPERO__)
    // Platform specific defines for PS5
    #undef NIM_PLATFORM_PS5
    #define NIM_PLATFORM_PS5 1
    #undef NIM_PLATFORM_PROSPERO
    #define NIM_PLATFORM_PROSPERO 1

    #define NIM_PLATFORM_NAME "PS5"
    #define NIM_PLATFORM_CONSOLE 1

    // Generic platform defines for PSX
    #define NIM_PLATFORM_SONY 1
    #define NIM_PLATFORM_POSIX 1

#else
    #error Unknown Sony platform
#endif

// TODO: Currently this only likely detects xbox one, need to add xbox series x
#elif defined(NIM_PLATFORM_XBOXONE) || defined(_DURANGO) || defined(_XBOX_ONE) || defined(_GAMING_XBOX)
    #undef NIM_PLATFORM_XBOXONE
    #define NIM_PLATFORM_XBOXONE 1

    // Generic platform define for Xbox
    #undef NIM_PLATFORM_DURANGO
    #define NIM_PLATFORM_DURANGO 1

    #if !defined(_DURANGO)
        #define _DURANGO
    #endif

    #define NIM_PLATFORM_NAME "Xbox One"
    #define NIM_PLATFORM_CONSOLE 1
    #define NIM_PLATFORM_MICROSOFT 1

    // WINAPI_FAMILY defines - mirrored from winapifamily.h
    #define NIM_WINAPI_FAMILY_APP         1000
    #define NIM_WINAPI_FAMILY_DESKTOP_APP 1001
    #define NIM_WINAPI_FAMILY_PHONE_APP   1002
    #define NIM_WINAPI_FAMILY_TV_APP      1003
    #define NIM_WINAPI_FAMILY_TV_TITLE    1004
    #define NIM_WINAPI_FAMILY_GAMES       1006

    #if defined(WINAPI_FAMILY)
        #include <winapifamily.h>
		#if defined(WINAPI_FAMILY_TV_TITLE) && WINAPI_FAMILY == WINAPI_FAMILY_TV_TITLE
			#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_TV_TITLE
		#elif defined(WINAPI_FAMILY_DESKTOP_APP) && WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
			#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_DESKTOP_APP
		#elif defined(WINAPI_FAMILY_GAMES) && WINAPI_FAMILY == WINAPI_FAMILY_GAMES
			#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_GAMES
		#else
			#error Unsupported WINAPI_FAMILY
		#endif
    #else
        #error WINAPI_FAMILY should always be defined on Xbox One.
    #endif

    // Macro to determine if a partition is enabled.
    #define NIM_WINAPI_FAMILY_PARTITION(Partition)	(Partition)

    #if NIM_WINAPI_FAMILY == NIM_WINAPI_FAMILY_DESKTOP_APP
        #define NIM_WINAPI_PARTITION_CORE     1
        #define NIM_WINAPI_PARTITION_DESKTOP  1
        #define NIM_WINAPI_PARTITION_APP      1
        #define NIM_WINAPI_PARTITION_PC_APP   0
        #define NIM_WIANPI_PARTITION_PHONE    0
        #define NIM_WINAPI_PARTITION_TV_APP   0
        #define NIM_WINAPI_PARTITION_TV_TITLE 0
        #define NIM_WINAPI_PARTITION_GAMES    0
    #elif NIM_WINAPI_FAMILY == NIM_WINAPI_FAMILY_TV_TITLE
        #define NIM_WINAPI_PARTITION_CORE     1
		#define NIM_WINAPI_PARTITION_DESKTOP  0
		#define NIM_WINAPI_PARTITION_APP      0
		#define NIM_WINAPI_PARTITION_PC_APP   0
		#define NIM_WIANPI_PARTITION_PHONE    0
		#define NIM_WINAPI_PARTITION_TV_APP   0
		#define NIM_WINAPI_PARTITION_TV_TITLE 1
		#define NIM_WINAPI_PARTITION_GAMES    0
	#elif NIM_WINAPI_FAMILY == NIM_WINAPI_FAMILY_GAMES
		#define NIM_WINAPI_PARTITION_CORE     1
		#define NIM_WINAPI_PARTITION_DESKTOP  0
		#define NIM_WINAPI_PARTITION_APP      0
		#define NIM_WINAPI_PARTITION_PC_APP   0
		#define NIM_WIANPI_PARTITION_PHONE    0
		#define NIM_WINAPI_PARTITION_TV_APP   0
		#define NIM_WINAPI_PARTITION_TV_TITLE 0
		#define NIM_WINAPI_PARTITION_GAMES    1
	#else
		#error Unsupported WINAPI_FAMILY
    #endif

    #if NIM_WINAPI_FAMILY_PARTITION(NIM_WINAPI_PARTITION_GAMES)
    #define CS_UNDEFINED_STRING 			1
            #define CS_UNDEFINED_STRING 		1
    #endif

    #if NIM_WINAPI_FAMILY_PARTITION(NIM_WINAPI_PARTITION_TV_TITLE)
    #define NIM_PLATFORM_XBOXONE_XDK 	1
    #endif


#elif (defined(NIM_PLATFORM_WINDOWS) || (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64))) && !defined(CS_UNDEFINED_STRING)
	#undef NIM_PLATFORM_WINDOWS
	#define NIM_PLATFORM_WINDOWS 1
	#define NIM_PLATFORM_NAME "Windows"

	#ifdef _WIN64 // VC++ defines both _WIN32 and _WIN64 when compiling for Win64.
		#define NIM_PLATFORM_WIN64 1
	#else
		#define NIM_PLATFORM_WIN32 1
	#endif

	#define NIM_PLATFORM_DESKTOP 1
	#define NIM_PLATFORM_MICROSOFT 1

	// WINAPI_FAMILY defines to support Windows 8 Metro Apps - mirroring winapifamily.h in the Windows 8 SDK
	#define NIM_WINAPI_FAMILY_APP 1000
	#define NIM_WINAPI_FAMILY_DESKTOP_APP 1001
	#define NIM_WINAPI_FAMILY_GAMES 1006

	#if defined(WINAPI_FAMILY)
		#if defined(_MSC_VER)
			#pragma warning(push, 0)
		#endif
		#include <winapifamily.h>
		#if defined(_MSC_VER)
			#pragma warning(pop)
		#endif
		#if defined(WINAPI_FAMILY_DESKTOP_APP) && WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
			#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_DESKTOP_APP
		#elif defined(WINAPI_FAMILY_APP) && WINAPI_FAMILY == WINAPI_FAMILY_APP
			#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_APP
		#elif defined(WINAPI_FAMILY_GAMES) && WINAPI_FAMILY == WINAPI_FAMILY_GAMES
			#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_GAMES
		#else
			#error Unsupported WINAPI_FAMILY
		#endif
	#else
		#define NIM_WINAPI_FAMILY NIM_WINAPI_FAMILY_DESKTOP_APP
	#endif

	#define NIM_WINAPI_PARTITION_DESKTOP 1
	#define NIM_WINAPI_PARTITION_APP 1
	#define NIM_WINAPI_PARTITION_GAMES (NIM_WINAPI_FAMILY == NIM_WINAPI_FAMILY_GAMES)

	#define NIM_WINAPI_FAMILY_PARTITION(Partition) (Partition)

	// NIM_PLATFORM_WINRT
	// This is a subset of Windows which is used for tablets and the "Metro" (restricted) Windows user interface.
	// WinRT doesn't have access to the Windows "desktop" API, but WinRT can nevertheless run on
	// desktop computers in addition to tablets. The Windows Phone API is a subset of WinRT and is not included
	// in it due to it being only a part of the API.
	#if defined(__cplusplus_winrt)
		#define NIM_PLATFORM_WINRT 1
	#endif

#elif defined(__APPLE__) && __APPLE__
	#include <TargetConditionals.h>

	// Apple family of operating systems.
	#define NIM_PLATFORM_APPLE
	#define NIM_PLATFORM_POSIX 1

	// iPhone
	// TARGET_OS_IPHONE will be undefined on an unknown compiler, and will be defined on gcc.
	#if defined(NIM_PLATFORM_IPHONE) || defined(__IPHONE__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE) ||                                             \
		(defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR)
		#undef NIM_PLATFORM_IPHONE
		#define NIM_PLATFORM_IPHONE 1
		#define NIM_PLATFORM_NAME "iPhone"
		#define NIM_POSIX_THREADS_AVAILABLE 1

		#define NIM_PLATFORM_MOBILE 1

	// Macintosh OSX
	// __i386__ and __intel__ are defined by the GCC compiler.
	// __MACH__ is defined by the GCC compiler.
	#elif defined(NIM_PLATFORM_OSX) || defined(__MACH__)
		#undef NIM_PLATFORM_OSX
		#define NIM_PLATFORM_OSX 1
		#define NIM_PLATFORM_UNIX 1
		#define NIM_PLATFORM_POSIX 1
		#define NIM_PLATFORM_NAME "OSX"

		#define NIM_PLATFORM_DESKTOP 1
	#else
		#error Unknown Apple Platform
	#endif

#elif defined(NIM_PLATFORM_LINUX) || (defined(__linux) || defined(__linux__))
	#undef NIM_PLATFORM_LINUX
	#define NIM_PLATFORM_LINUX 1
	#define NIM_PLATFORM_UNIX 1
	#define NIM_PLATFORM_POSIX 1
	#define NIM_PLATFORM_NAME "Linux"

	#define NIM_PLATFORM_DESKTOP 1

#elif defined(NIM_PLATFORM_ANDROID) || defined(__ANDROID__)
	#undef NIM_PLATFORM_ANDROID
	#define NIM_PLATFORM_ANDROID 1
	#define NIM_PLATFORM_LINUX 1
	#define NIM_PLATFORM_UNIX 1
	#define NIM_PLATFORM_POSIX 1

	#define NIM_PLATFORM_MOBILE 1

#else
	#error Unknown platform
#endif


