#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#define FRAMERATE 60

int main() {
    sf::RenderWindow window;

    sf::ConvexShape spaceship;

    // settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // set window
    window.create(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE);

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
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    std::cout << "[INFO] - Closing window!" << std::endl;
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Right) {
                    spaceship.setRotation(spaceship.getRotation() + 10.0f);
                }
            }
        }

        window.clear(sf::Color::Black);

        // draw here
        window.draw(spaceship);

        window.display();
    }
}
