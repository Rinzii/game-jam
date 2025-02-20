if (WIN32)
    # disable deprecation warnings
    target_compile_definitions(editor PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()

# If editor is being built create a global define that launcher and other areas can use
if (NIMBUS_BUILD_EDITOR)
    target_compile_definitions(editor PUBLIC CONFIG_NIMBUS_HAS_EDITOR)
endif ()