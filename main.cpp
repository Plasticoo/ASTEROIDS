#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#define FRAMERATE 60

int main() {
    sf::RenderWindow window;

    // TODO: cant be a circleshape, and shouldnt
    sf::CircleShape spaceship(15, 3);

    // set window
    window.create(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE);

    spaceship.setOrigin(spaceship.getRadius() / 4, spaceship.getRadius() / 4);
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
