if (WIN32)
    # disable deprecation warnings
    target_compile_definitions(nimbus PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()

if (NIMBUS_ENABLE_PROFILER AND NOT DEFINED NIMBUS_PRODUCTION_BUILD)
    target_compile_definitions(nimbus PRIVATE TRACY_ENABLE)
    target_compile_definitions(nimbus PRIVATE CONFIG_NIMBUS_PROFILER)
endif ()

if (DEFINED NIMBUS_PRODUCTION_BUILD)
    target_compile_definitions(nimbus INTERFACE CONFIG_NIMBUS_PRODUCTION)
endif ()