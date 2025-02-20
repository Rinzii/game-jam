if (FORNANI_PRODUCTION_BUILD)
    if (FORNANI_ENABLE_PROFILER)
        message(FATAL_ERROR "FORNANI: FORNANI_PRODUCTION_BUILD is ON, but FORNANI_ENABLE_PROFILER is also ON. You should not profile in production!")
    endif ()

    if (FORNANI_ENABLE_VERBOSE_LOGGING)
        message(WARNING "FORNANI: FORNANI_PRODUCTION_BUILD is ON, but FORNANI_ENABLE_VERBOSE_LOGGING is also ON. Did you mean to do this?")
    endif ()
endif ()

if (FORNANI_BUILD_EDITOR)
    message(STATUS "FORNANI: Building editor & launcher!")
else ()
    message(STATUS "FORNANI: Building launcher!")
endif ()

if (FORNANI_ENABLE_PROFILER)
    message(STATUS "FORNANI: FORNANI_ENABLE_PROFILER is ON. Profiling will now be enabled in the executable!")
endif ()

if (FORNANI_ENABLE_VERBOSE_LOGGING)
    message(STATUS "FORNANI: FORNANI_ENABLE_VERBOSE_LOGGING is ON. Logger will now output verbose logging information!")
endif ()
