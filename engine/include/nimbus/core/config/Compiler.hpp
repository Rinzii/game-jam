#pragma once

/*
 * Currently supported defines include:
 *      NIM_COMPILER_MSVC
 *      NIM_COMPILER_GCC
 *      NIM_COMPILER_CLANG
 *      NIM_COMPILER_CLANG_CL
 *
 *      NIM_COMPILER_VERSION = <integer>
 *      NIM_COMPILER_NAME = <string>
 *      NIM_COMPILER_STRING = <string>
 */

// Note: This is used to generate the NIM_COMPILER_STRING macros
#ifndef INTERNAL_STRINGIFY
	#define INTERNAL_STRINGIFY(x) INTERNAL_PRIMITIVE_STRINGIFY(x)
#endif
#ifndef INTERNAL_PRIMITIVE_STRINGIFY
	#define INTERNAL_PRIMITIVE_STRINGIFY(x) #x
#endif

// Clang's GCC-compatible driver.
#if defined(__clang__) && !defined(_MSC_VER)
	#define NIM_COMPILER_CLANG	 1
	#define NIM_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
	#define NIM_COMPILER_NAME	 "clang"
	#define NIM_COMPILER_STRING	 NIM_COMPILER_NAME __clang_version__

// GCC (a.k.a. GNUC)
#elif defined(__GNUC__)
	// Define interchangeably between GCC and GNUC. Though NIM_COMPILER_GCC is preferred.
	#define NIM_COMPILER_GCC	 1
	#define NIM_COMPILER_GNUC	 1
	#define NIM_COMPILER_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
	#define NIM_COMPILER_NAME	 "GCC"
	#define NIM_COMPILER_STRING	 NIM_COMPILER_NAME " compiler, version " INTERNAL_STRINGIFY(__GNUC__) "." INTERNAL_STRINGIFY(__GNUC_MINOR__)

#elif defined(_MSC_VER) // TODO: Validate everything is properly being set for MSVC
	#define NIM_COMPILER_MSVC	   1
	#define NIM_COMPILER_MICROSOFT 1
	#define NIM_COMPILER_VERSION   _MSC_VER
	#define NIM_COMPILER_NAME	   "Microsoft Visual C++"
	#define NIM_COMPILER_STRING	   NIM_COMPILER_NAME " compiler, version " INTERNAL_STRINGIFY(_MSC_VER)

	#if defined(__clang__)
		// Clang's MSVC-compatible driver.
		#define NIM_COMPILER_CLANG_CL 1
	#endif

#endif