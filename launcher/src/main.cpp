#include "nimbus/io/Logger.hpp"
#include "nimbus/io/PathHelpers.hpp"

static constexpr auto logFile{"nimbus.log"};

nim::io::Logger const main_logger{"Main"};

int main() {

    // TODO: Maybe we should just have the entire startup use a config file of some sort to setup the engine and game?

    // TODO: Maybe move this into a config file?
    const auto config = nim::io::logger::Config{};
    // Required to initialize the logger for the application. This must also stay outside any try/catch block.
    auto log_instance = nim::io::logger::Instance{logFile, config};

    // We should always use our helpers to get the exe directory.
    const auto exe_dir = nim::io::abs_exe_directory();

    NIM_LOG_INFO(main_logger, "Found exe at: {}", exe_dir.string());

    // How to distinguish if we have an editor or not
#if defined(CONFIG_NIMBUS_HAS_EDITOR)
    NIM_LOG_INFO(main_logger, "Found editor at: {}", exe_dir.string());
#endif

#if defined(CONFIG_NIMBUS_PRODUCTION)
    NIM_LOG_INFO(main_logger, "Production build is set!");
#endif

    return 0;
}
