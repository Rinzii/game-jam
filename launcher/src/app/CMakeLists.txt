nim_add_sources(
        app_icon_data.hpp
)

if (WIN32)
    # On windows this will set the executables icon. This must ALWAYS be added as the last source file.
    nim_add_sources(
            app.rc
    )
endif ()
