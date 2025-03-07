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

// TODO: This should work fine on clang based compilers, but I still need to validate this is fact.
// TODO: I need to validate that clang-cl works with this as well on windows.

///
/// \def NIM_DISABLE_CLANG_WARNING(w)
/// \brief Disables a warning for Clang.
/// \param w The warning to disable as an error. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be disabled per statement, due to how clang works.
///
/// Example usage of macro:
///     NIM_DISABLE_CLANG_WARNING(-Wuninitialized)
///     NIM_DISABLE_CLANG_WARNING(-Wunused)
///     <code>
///     NIM_RESTORE_CLANG_WARNING()
///     NIM_RESTORE_CLANG_WARNING()
///
#ifndef NIM_DISABLE_CLANG_WARNING
	#if defined(__clang__)
	// Disable clang format so it does not format "-Wunknown-warning-option" to "- Wunknown - Wwarning - Woption"
	// clang-format off
		#define NIM_CLANG_WHELP0(x) #x											 // Helper macros - do not use directly
		#define NIM_CLANG_WHELP1(x) NIM_CLANG_WHELP0(clang diagnostic ignored x) // Helper macros - do not use directly
		#define NIM_CLANG_WHELP2(x) NIM_CLANG_WHELP1(#x)						 // Helper macros - do not use directly

		// Disables a warning for Clang. This should be written as -Wwarning-name and not as a string.
		// Must be called before NIM_RESTORE_CLANG_WARNING().
		#define NIM_DISABLE_CLANG_WARNING(w)                                                                                                                  \
			_Pragma("clang diagnostic push") _Pragma(NIM_CLANG_WHELP2(-Wunknown-warning-option)) _Pragma(NIM_CLANG_WHELP2(w))
	// clang-format on
	#else
	// If not on Clang, this macro does nothing.
	// Must be called before NIM_RESTORE_CLANG_WARNING().
		#define NIM_DISABLE_CLANG_WARNING(w)
	#endif
#endif

///
/// \def NIM_RESTORE_CLANG_WARNING()
/// \brief Restore a warning for Clang.
/// \param w The warning to disable as an error. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be disabled per statement, due to how clang works.
///
/// Example usage of macro:
///     NIM_DISABLE_CLANG_WARNING(-Wuninitialized)
///     NIM_DISABLE_CLANG_WARNING(-Wunused)
///     <code>
///     NIM_RESTORE_CLANG_WARNING()
///     NIM_RESTORE_CLANG_WARNING()
///
#ifndef NIM_RESTORE_CLANG_WARNING
	#if defined(__clang__)
		// Restore a warning for Clang in a stack-based manner.
		// Must be called after NIM_DISABLE_CLANG_WARNING(w).
		#define NIM_RESTORE_CLANG_WARNING() _Pragma("clang diagnostic pop")
	#else
	// If not on Clang, this macro does nothing.
	// Must be called after NIM_DISABLE_CLANG_WARNING(w).
		#define NIM_RESTORE_CLANG_WARNING()
	#endif
#endif

///
/// \def NIM_ENABLE_CLANG_WARNING_AS_ERROR(w)
/// \brief This will enable a warning as an error for clang.
/// \param w The warning to enable as an error. This should be written as -Wwarning-name and not as a string.
/// \note Only one warning can be treated as an error per statement, due to how clang works.
///
/// Example usage of macro:
///     NIM_ENABLE_CLANG_WARNING_AS_ERROR(-Wuninitialized)
///     NIM_ENABLE_CLANG_WARNING_AS_ERROR(-Wunused)
///     <code>
///     NIM_DISABLE_CLANG_WARNING_AS_ERROR()
///     NIM_DISABLE_CLANG_WARNING_AS_ERROR()
///
#ifndef NIM_ENABLE_CLANG_WARNING_AS_ERROR
	#if defined(__clang__)
		// Helper macros
		#define NIM_CLANG_WERROR_HELP0(x) #x											   // Helper macros - do not use directly
		#define NIM_CLANG_WERROR_HELP1(x) NIM_CLANG_WERROR_HELP0(clang diagnostic error x) // Helper macros - do not use directly
		#define NIM_CLANG_WERROR_HELP2(x) NIM_CLANG_WERROR_HELP1(#x)					   // Helper macros - do not use directly

		// This will enable a warning as an error for clang. This should be written as -Wwarning-name and not as a string.
		// Must be called before NIM_DISABLE_CLANG_WARNING_AS_ERROR().
		#define NIM_ENABLE_CLANG_WARNING_AS_ERROR(w) _Pragma("clang diagnostic push") _Pragma(NIM_CLANG_WERROR_HELP2(w))
	#else
	// If not on clang, this macro does nothing.
	// Must be called before NIM_DISABLE_CLANG_WARNING_AS_ERROR().
		#define NIM_ENABLE_CLANG_WARNING_AS_ERROR(w)
	#endif
#endif

///
/// \def NIM_DISABLE_CLANG_WARNING_AS_ERROR()
/// \brief This will disable a warning as an error for clang.
/// \note Only one warning can be treated as an error per statement, due to how clang works.
///
/// Example usage of macro:
///     NIM_ENABLE_CLANG_WARNING_AS_ERROR(-Wuninitialized)
///     NIM_ENABLE_CLANG_WARNING_AS_ERROR(-Wunused)
///     <code>
///     NIM_DISABLE_CLANG_WARNING_AS_ERROR()
///     NIM_DISABLE_CLANG_WARNING_AS_ERROR()
///
#ifndef NIM_DISABLE_CLANG_WARNING_AS_ERROR
	#if defined(__clang__)
		// This will disable a warning as an error for clang in a stack-based manner.
		// Must be called after NIM_ENABLE_CLANG_WARNING_AS_ERROR(w).
		#define NIM_DISABLE_CLANG_WARNING_AS_ERROR() _Pragma("clang diagnostic pop")
	#else
	// If not on clang, this macro does nothing.
	// Must be called after NIM_ENABLE_CLANG_WARNING_AS_ERROR(w).
		#define NIM_DISABLE_CLANG_WARNING_AS_ERROR()
	#endif
#endif