#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
using namespace std;

sf::Vector2f normalizeVctr(sf::Vector2f vec) {
  float square = pow(vec.x, 2) + pow(vec.y, 2);
  float magnitude = sqrt(square);
  sf::Vector2f normalizeVctr;
  normalizeVctr.x = vec.x / magnitude;
  normalizeVctr.y = vec.y / magnitude;

  return normalizeVctr;
}

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
  sf::Texture playerTexture("assets/hero/BODY_skeleton.png", false,
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

  //---------------------------Calculate bullet direction ----------------
  vector<sf::RectangleShape> bullets;
  float bulletSpeed = 2.0f;
  sf::Vector2f bulletDirection;
  //--------------------Calculate bullet bulletDirection----------------
  //------------------------------GAME-----------------------------
  // game loop

  while (window.isOpen()) {
    // event loop
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    //  Movement (basic)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
      playerSprite.move({0.f, -60.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
      playerSprite.move({-60.f, 0.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
      playerSprite.move({0.f, 60.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
      playerSprite.move({60.f, 0.f});

    // multiple bullets
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      bullets.push_back(sf::RectangleShape({25.f, 10.f}));

      int lastBullet = bullets.size() - 1;
      bullets[lastBullet].setPosition(playerSprite.getPosition());
      bulletDirection =
          enemySprite.getPosition() - bullets[lastBullet].getPosition();
      bulletDirection = normalizeVctr(bulletDirection);
    }

    for (int i = 0; i < bullets.size(); i++) {
      bullets[i].setPosition(bullets[i].getPosition() +
                             bulletDirection * bulletSpeed);
    }

    //--------DRAW------
    window.clear(sf::Color::Black);
    window.draw(playerSprite);
    window.draw(enemySprite);

    for (int i = 0; i < bullets.size(); i++) {
      window.draw(bullets[i]);
    }
    window.display();
    //--------DRAW------
  }
  return 0;
  //------------------------------GAME-----------------------------
}
