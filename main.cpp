#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main() {
    //------------------------------INITIALIZE-----------------------------
    // antialiasing
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({1920, 1200}), "My window",
                            sf::State::Windowed, settings);
    window.setFramerateLimit(60);
    //------------------------------INITIALIZE-----------------------------

    //------------------------------LOAD-----------------------------
    int XIndex = 3;
    int YIndex = 0;
    sf::Texture playerTexture(
        "assets/hero/BODY_skeleton.png", false,
        sf::IntRect({XIndex * 64, YIndex * 64}, {64, 64}));

    sf::Texture enemyTexture("assets/hero/BODY_dummy.png", false,
                             sf::IntRect({XIndex * 64, YIndex * 64}, {64, 64}));

    sf::Sprite playerSprite(playerTexture);
    sf::Sprite enemySprite(enemyTexture);

    playerSprite.setScale({1.5, 1.5});
    playerSprite.setPosition({896.f, 536.f});
    enemySprite.setScale({1.5, 1.5});
    enemySprite.setPosition({1720.f, 536.f});
    //------------------------------LOAD-----------------------------

    //------------------------------GAME-----------------------------
    // game loop

    while (window.isOpen()) {
        // event loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        // Movement (basic)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            playerSprite.move({0.f, -1.0f});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            playerSprite.move({-1.0f, 0.f});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            playerSprite.move({0.f, 1.0f});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            playerSprite.move({1.0f, 0.f});

        window.clear(sf::Color::Black);
        window.draw(playerSprite);
        window.draw(enemySprite);
        window.display();
    }
    return 0;
    //------------------------------GAME-----------------------------
}
