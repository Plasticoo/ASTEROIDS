#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#define FRAMERATE 60
#define PI 3.14159265f

int main() {
    bool focus = true;

    sf::RenderWindow window;
    sf::ConvexShape spaceship;

    // settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // set window
    window.create(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE);

    // set spaceship
    spaceship.setPointCount(3);
    spaceship.setPoint(0, sf::Vector2f(20, 40));
    spaceship.setPoint(1, sf::Vector2f(70, 60));
    spaceship.setPoint(2, sf::Vector2f(20, 80));

    spaceship.setOrigin((20 + 70 + 20) / 3, (40 + 60 + 80) / 3);
    spaceship.setFillColor(sf::Color::Cyan);
    spaceship.setPosition(800/2, 600/2);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "[INFO] - Closing window!" << std::endl;
                window.close();
            }

            if (event.type == sf::Event::GainedFocus && !focus) {
                focus = true;
            }

            if (event.type == sf::Event::LostFocus && focus) {
                focus = false;
            }
        }

        if (focus) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                std::cout << "[INFO] - Closing window!" << std::endl;
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                spaceship.setRotation(spaceship.getRotation() - 1.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                spaceship.setRotation(spaceship.getRotation() + 1.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                spaceship.move(std::cos(PI * spaceship.getRotation() / 180.f),
                               std::sin(PI * spaceship.getRotation() / 180.f));
            }
        }
        window.clear(sf::Color::Black);

        // draw here
        window.draw(spaceship);

        window.display();
    }
}
