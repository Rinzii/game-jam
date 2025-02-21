#include "nimbus/io/Logger.hpp"
#include "nimbus/io/PathHelpers.hpp"

#include <SFML/Graphics.hpp>

#include <rpmalloc.h>

#include <optional>
#include <cstdlib>

#include "app/app_icon_data.hpp"

static constexpr auto logFile{"nimbus.log"};

nim::io::Logger const main_logger{"Main"};

int main() {

    rpmalloc_initialize(); // Needed for rpmalloc to work.

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

    sf::Image image;
    // Load the image from memory using the embedded array's data and size
    if (!image.loadFromMemory(generated::icon_png.data(), generated::icon_png.size())) {
        // Maybe log?
    }

    // TODO: Remove once project starts.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Starter");

    window.setIcon(image.getSize(), image.getPixelsPtr());

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({350.f, 250.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    rpmalloc_finalize();
    return EXIT_SUCCESS;
}
