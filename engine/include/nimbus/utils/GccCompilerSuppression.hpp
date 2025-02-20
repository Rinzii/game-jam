/*
 * Copyright (c) Ian Pike
 * Copyright (c) CCMath contributors
 *
 * CCMath is provided under the Apache-2.0 License WITH LLVM-exception.
 * See LICENSE for more information.
 *
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

// Taken from CCMath with my own permission. Modified to fit Nimbus.

#pragma once

// TODO: This should work fine on gcc based compilers, but I still need to validate this is fact.

///
/// \def NIM_DISABLE_GCC_WARNING(w)
/// \brief Disables a warning for GCC.
/// \param w The warning to disable as an error. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be disabled per statement due to how gcc works.
/// \note This macro must be called before NIM_RESTORE_GCC_WARNING().
///
/// Example usage of macro:
///     NIM_DISABLE_GCC_WARNING(-Wuninitialized)
///     NIM_DISABLE_GCC_WARNING(-Wunused)
///     <code>
///     NIM_RESTORE_GCC_WARNING()
///     NIM_RESTORE_GCC_WARNING()
///
#ifndef NIM_DISABLE_GCC_WARNING
	#if defined(__GNUC__) && !defined(__clang__)
		// Helper macros - do not use directly
		#define NIM_GCC_WHELP0(x) #x
		#define NIM_GCC_WHELP1(x) NIM_GCC_WHELP0(GCC diagnostic ignored x)
		#define NIM_GCC_WHELP2(x) NIM_GCC_WHELP1(#x)

		// Disables a warning for GCC. This should be written as -Wwarning-name and not as a string.
		// Must be called before NIM_RESTORE_GCC_WARNING().
		#define NIM_DISABLE_GCC_WARNING(w) _Pragma("GCC diagnostic push") _Pragma(NIM_GCC_WHELP2(w))
	#else
	// If not on GCC, this macro does nothing.
	// Must be called before NIM_RESTORE_GCC_WARNING().
		#define NIM_DISABLE_GCC_WARNING(w)
	#endif
#endif

///
/// \def NIM_RESTORE_GCC_WARNING()
/// \brief Restore a warning for GCC. Warnings are restored in a stack-based manner.
/// \note Only one warning can be disabled per statement due to how gcc works.
/// \note This macro must be called after NIM_DISABLE_GCC_WARNING(w).
///
/// Example usage of macro:
///     NIM_DISABLE_GCC_WARNING(-Wuninitialized)
///     NIM_DISABLE_GCC_WARNING(-Wunused)
///     <code>
///     NIM_RESTORE_GCC_WARNING()
///     NIM_RESTORE_GCC_WARNING()
///
#ifndef NIM_RESTORE_GCC_WARNING
	#if defined(__GNUC__) && !defined(__clang__)
		// Restore a warning for GCC in a stack-based manner.
		// Must be called after NIM_DISABLE_GCC_WARNING(w).
		#define NIM_RESTORE_GCC_WARNING() _Pragma("GCC diagnostic pop")
	#else
	// If not on GCC, this macro does nothing.
	// Must be called after NIM_DISABLE_GCC_WARNING(w).
		#define NIM_RESTORE_GCC_WARNING()
	#endif
#endif

///
/// \def NIM_ENABLE_GCC_WARNING_AS_ERROR(w)
/// \brief This will enable a warning as an error for GCC.
/// \param w The warning to enable as an error. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be treated as an error per statement due to how GCC works.
/// \note This macro must be called before NIM_DISABLE_GCC_WARNING_AS_ERROR().
///
/// Example usage of macro:
///     NIM_ENABLE_GCC_WARNING_AS_ERROR(-Wuninitialized)
///     NIM_ENABLE_GCC_WARNING_AS_ERROR(-Wunused)
///     <code>
///     NIM_DISABLE_GCC_WARNING_AS_ERROR()
///     NIM_DISABLE_GCC_WARNING_AS_ERROR()
///
#ifndef NIM_ENABLE_GCC_WARNING_AS_ERROR
	#if defined(__GNUC__) && !defined(__clang__)
		#define NIM_GCC_WERROR_HELP0(x) #x											 // Helper macros - do not use directly
		#define NIM_GCC_WERROR_HELP1(x) NIM_GCC_WERROR_HELP0(GCC diagnostic error x) // Helper macros - do not use directly
		#define NIM_GCC_WERROR_HELP2(x) NIM_GCC_WERROR_HELP1(#x)					 // Helper macros - do not use directly

		// This will enable a warning as an error for GCC. This should be written as -Wwarning-name and not as a string.
		// Must be called before NIM_DISABLE_GCC_WARNING_AS_ERROR().
		#define NIM_ENABLE_GCC_WARNING_AS_ERROR(w) _Pragma("GCC diagnostic push") _Pragma(NIM_GCC_WERROR_HELP2(w))
	#else
	// If not on GCC, this macro does nothing.
	// Must be called before NIM_DISABLE_GCC_WARNING_AS_ERROR().
		#define NIM_ENABLE_GCC_WARNING_AS_ERROR(w)
	#endif
#endif

///
/// \def NIM_DISABLE_GCC_WARNING_AS_ERROR()
/// \brief This will disable a warning as an error for GCC.
/// \note Only one warning can be treated as an error per statement, due to how GCC works
///
/// Example usage of macro:
///     NIM_ENABLE_GCC_WARNING_AS_ERROR(-Wuninitialized)
///     NIM_ENABLE_GCC_WARNING_AS_ERROR(-Wunused)
///     <code>
///     NIM_DISABLE_GCC_WARNING_AS_ERROR()
///     NIM_DISABLE_GCC_WARNING_AS_ERROR()
///
#ifndef NIM_DISABLE_GCC_WARNING_AS_ERROR
	#if defined(__GNUC__) && !defined(__clang__)
		// This will disable a warning as an error for GCC in a stack-based manner.
		// Must be called after NIM_ENABLE_GCC_WARNING_AS_ERROR(w).
		#define NIM_DISABLE_GCC_WARNING_AS_ERROR() _Pragma("GCC diagnostic pop")
	#else
	// If not on GCC, this macro does nothing.
	// Must be called after NIM_ENABLE_GCC_WARNING_AS_ERROR(w).
		#define NIM_DISABLE_GCC_WARNING_AS_ERROR()
	#endif
#endif

///
/// \def NIM_ENABLE_IGNORE_GCC_WARNING(w)
/// \brief This will enable the suppression of a warning on GCC.
/// \param w The warning to enable as an error. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be treated as an error per statement, due to how GCC works.
///
/// Example usage of macro:
///     NIM_ENABLE_IGNORE_GCC_WARNING(-Wuninitialized)
///     NIM_ENABLE_IGNORE_GCC_WARNING(-Wunused)
///     <code>
///     NIM_DISABLE_IGNORE_GCC_WARNING(-Wuninitialized)
///     NIM_DISABLE_IGNORE_GCC_WARNING(-Wunused)
///
#ifndef NIM_ENABLE_IGNORE_GCC_WARNING
	#if defined(__GNUC__) && !defined(__clang__)
		#define NIM_GCC_IGNORE_HELP0(x) #x											   // Helper macros - do not use directly
		#define NIM_GCC_IGNORE_HELP1(x) NIM_GCC_IGNORE_HELP0(GCC diagnostic ignored x) // Helper macros - do not use directly
		#define NIM_GCC_IGNORE_HELP2(x) NIM_GCC_IGNORE_HELP1(#x)					   // Helper macros - do not use directly

		// This will enable the suppression of a warning on GCC. This should be written as -Wwarning-name and not as a string.
		// Must be called before NIM_DISABLE_IGNORE_GCC_WARNING(w).
		#define NIM_ENABLE_IGNORE_GCC_WARNING(w) _Pragma("GCC diagnostic push") _Pragma(NIM_GCC_IGNORE_HELP2(w))
	#else
	// If not on GCC, this macro does nothing.
	// Must be called before NIM_DISABLE_IGNORE_GCC_WARNING(w).
		#define NIM_ENABLE_IGNORE_GCC_WARNING(w)
	#endif
#endif

///
/// \def NIM_DISABLE_IGNORE_GCC_WARNING(w)
/// \brief This will re-enable an ignored warning for GCC.
/// \param w The warning to re-enable as a warning. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be treated as an error per statement, due to how GCC works
///
/// Example usage of macro:
///     NIM_ENABLE_IGNORE_GCC_WARNING(-Wuninitialized)
///     NIM_ENABLE_IGNORE_GCC_WARNING(-Wunused)
///     <code>
///     NIM_DISABLE_IGNORE_GCC_WARNING(-Wuninitialized)
///     NIM_DISABLE_IGNORE_GCC_WARNING(-Wunused)
///
#ifndef NIM_DISABLE_IGNORE_GCC_WARNING
	#if defined(__GNUC__) && !defined(__clang__)
		#ifndef NIM_GCC_IGNORE_DISABLE_HELP0
			#define NIM_GCC_IGNORE_DISABLE_HELP0(x) #x // Helper macros - do not use directly
		#endif
		#ifndef NIM_GCC_IGNORE_DISABLE_HELP1
			#define NIM_GCC_IGNORE_DISABLE_HELP1(x) NIM_GCC_IGNORE_DISABLE_HELP0(GCC diagnostic warning x) // Helper macros - do not use directly
		#endif
		#ifndef NIM_GCC_IGNORE_DISABLE_HELP2
			#define NIM_GCC_IGNORE_DISABLE_HELP2(x) NIM_GCC_IGNORE_DISABLE_HELP1(#x) // Helper macros - do not use directly
		#endif
		// This will disable suppression of an ignored warning for GCC
		// Must be called after NIM_ENABLE_IGNORE_GCC_WARNING(w).
		#define NIM_DISABLE_IGNORE_GCC_WARNING(w) _Pragma(NIM_GCC_IGNORE_DISABLE_HELP2(w)) _Pragma("GCC diagnostic pop")
	#else
	// If not on GCC, this macro does nothing.
	// Must be called after NIM_ENABLE_IGNORE_GCC_WARNING(w).
		#define NIM_DISABLE_IGNORE_GCC_WARNING(w)
	#endif
#endif