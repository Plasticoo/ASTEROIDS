#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#define FRAMERATE 60

int main() {
    sf::RenderWindow window;
    sf::ConvexShape spaceship;

    // set window
    window.create(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAMERATE);

    spaceship.setPointCount(4);
    spaceship.setPoint(0, sf::Vector2f(0, 0));
    spaceship.setPoint(1, sf::Vector2f(150, 10));
    spaceship.setPoint(2, sf::Vector2f(120, 90));
    spaceship.setPoint(3, sf::Vector2f(30, 100));

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "[INFO] - Closing window!" << std::endl;
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // draw here
        window.draw(spaceship);

        window.display();
    }
}
