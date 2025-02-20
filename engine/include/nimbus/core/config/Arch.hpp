
#pragma once

// Reference for all preprocessor macros used here
// https://sourceforge.net/p/predef/wiki/Architectures/
// https://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html
// https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
// https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/additional-predefined-macros.html
// https://developer.arm.com/documentation/dui0491/latest/Compiler-specific-Features/Predefined-macros

/// Identify what processor architecture we are compiling for.

/// x86 Architecture
// VS defines: _M_IX86
// GCC defines: i386, __i386, __i386__
#if defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(i386)
	#define NIM_ARCH_X86

/// x86_64 Architecture
// VS defines: _M_X64 and _M_AMD64
// GCC defines: __amd64__, __amd64, __x86_64__, and __x86_64
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
	#define NIM_ARCH_X64

/// ARM Architecture
// VS defines: _M_ARM
// GCC defines: __arm__
#elif defined(_M_ARM) || defined(__arm__)
	#define NIM_ARCH_ARM

/// ARM64 Architecture
// VS defines: _M_ARM64
// GCC defines: __aarch64__
#elif defined(_M_ARM64) || defined(__aarch64__)
	#define NIM_ARCH_ARM64

#else
	#error "Unknown architecture"
#endif


// NIM_MISALIGNED_SUPPORT_LEVEL
// Specifies if the processor can read and write built-in types that aren't
// naturally aligned.
//    0 - not supported. Likely causes an exception.
//    1 - supported but slow.
//    2 - supported and fast.
//
#ifndef NIM_MISALIGNED_SUPPORT_LEVEL
#if defined(NIM_ARCH_X64)
#define NIM_MISALIGNED_SUPPORT_LEVEL 2
#else
#define NIM_MISALIGNED_SUPPORT_LEVEL 0
#endif
#endif

// NOTE: Mirrored from riot/core/base/config/platform.h
// NOTE: This is being mirrored to avoid requiring the entire platform.h file to be included.

#ifndef NIM_PLATFORM_PTR_SIZE
#if defined(__WORDSIZE) // Defined by some variations of GCC.
#define NIM_PLATFORM_PTR_SIZE ((__WORDSIZE) / 8)
#elif defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(_M_IA64) || defined(__ia64__) || defined(__arch64__) || defined(__aarch64__) || defined(__mips64__) || defined(__64BIT__) || defined(__Ptr_Is_64)
#define NIM_PLATFORM_PTR_SIZE 8
#elif defined(__CC_ARM) && (__sizeof_ptr == 8)
#define NIM_PLATFORM_PTR_SIZE 8
	#else
		#define NIM_PLATFORM_PTR_SIZE 4
#endif
#endif

#ifndef NIM_PLATFORM_WORD_SIZE
#define NIM_PLATFORM_WORD_SIZE NIM_PLATFORM_PTR_SIZE
#endif

// NIM_CACHE_LINE_SIZE
// Specifies the cache line size broken down by compile target.
// This the expected best guess values for the targets that we can make at compilation time.

#ifndef NIM_CACHE_LINE_SIZE
#if   defined(NIM_ARCH_X86)
#define NIM_CACHE_LINE_SIZE 32    // This is the minimum possible value.
#elif defined(NIM_ARCH_X64)
#define NIM_CACHE_LINE_SIZE 64    // This is the minimum possible value
#elif defined(NIM_ARCH_ARM)
#define NIM_CACHE_LINE_SIZE 32    // This varies between implementations and is usually 32 or 64.
#elif defined(NIM_ARCH_ARM64)
#define NIM_CACHE_LINE_SIZE 64    // Cache line Cortex-A8  (64 bytes) http://shervinemami.info/armAssembly.html however this remains to be mostly an assumption at this stage
#elif (NIM_PLATFORM_WORD_SIZE == 4)
#define NIM_CACHE_LINE_SIZE 32    // This is the minimum possible value
#else
#define NIM_CACHE_LINE_SIZE 64    // This is the minimum possible value
#endif
#endif


#if defined(CONFIG_NIM_SIMD_ENABLE)

	// Identify if we are allowing simd instructions.
	#if defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
		#define NIM_SIMD_SSE 1
	#endif

	#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
		#define NIM_SIMD_SSE2 1
	#endif

	#if defined(__SSE3__)
		#define NIM_SIMD_SSE3 1
	#endif

	#if defined(__SSSE3__)
		#define NIM_SIMD_SSSE3 1
	#endif

	#if defined(__SSE4_1__)
		#define NIM_SIMD_SSE4_1 1
	#endif

	#if defined(__SSE4_2__)
		#define NIM_SIMD_SSE4_2 1
	#endif

	#if defined(__AVX__)
		#define NIM_SIMD_AVX 1
	#endif

	#if defined(__AVX2__)
		#define NIM_SIMD_AVX2 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Byte and Word instructions.
	#if defined(__AVX512BW__)
		#define NIM_SIMD_AVX512BW 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Conflict Detection instructions.
	#if defined(__AVX512CD__)
		#define NIM_SIMD_AVX512CD 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Doubleword and Quadword instructions.
	#if defined(__AVX512DQ__)
		#define NIM_SIMD_AVX512DQ 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Exponential and Reciprocal instructions.
	#if defined(__AVX512ER__)
		#define NIM_SIMD_AVX512ER 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Foundation instructions.
	#if defined(__AVX512F__)
		#define NIM_SIMD_AVX512F 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Prefetch instructions.
	#if defined(__AVX512PF__)
		#define NIM_SIMD_AVX512PF 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Vector Length extensions.
	#if defined(__AVX512VL__)
		#define NIM_SIMD_AVX512VL 1
	#endif

	#if defined(__ARM_NEON) || defined(__ARM_NEON__)
		#define NIM_SIMD_NEON 1
	#endif

	// If we have any simd instructions, then we define NIM_SIMD so that we can use it in our code.
	#if defined(NIM_SIMD_SSE) || defined(NIM_SIMD_SSE2) || defined(NIM_SIMD_SSE3) || defined(NIM_SIMD_SSSE3) || defined(NIM_SIMD_SSE4_1) ||                    \
		defined(NIM_SIMD_SSE4_2) || defined(NIM_SIMD_AVX) || defined(NIM_SIMD_AVX2) || defined(NIM_SIMD_AVX512BW) || defined(NIM_SIMD_AVX512CD) ||             \
		defined(NIM_SIMD_AVX512DQ) || defined(NIM_SIMD_AVX512ER) || defined(NIM_SIMD_AVX512F) || defined(NIM_SIMD_AVX512PF) || defined(NIM_SIMD_AVX512VL) ||   \
		defined(NIM_SIMD_NEON)
		#ifdef NIM_SIMD
			#undef NIM_SIMD
		#endif
		#define NIM_SIMD 1
	#else
		#error "NIM_SIMD defined but no valid simd instruction sets detected"
	#endif

#endif // defined(NIM_SIMD)