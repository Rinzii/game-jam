
if (WIN32)
    # disable deprecation warnings
    target_compile_definitions(nimbus_game PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()