#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#define FRAMERATE 60
#define PI 3.14159265f

struct Bullet {
    sf::RectangleShape object;
    sf::Vector2f original_pos;

    Bullet(sf::Vector2f position, float rotation) {
        this->object = sf::RectangleShape(sf::Vector2f(10, 10));
        this->object.setPosition(position);
        this->object.setRotation(rotation);

        this->original_pos = position;
    }
};

int main() {
    bool focus = true;

    sf::Font font;
    sf::Text text_points;
    sf::Text text_npoints;

    sf::RenderWindow window;
    sf::ConvexShape spaceship;

    // bullets
    std::vector<Bullet> bullets;

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

    if (!font.loadFromFile("resources/arial.ttf")) {
        printf("[ERRR] - Font could not be loaded.\n");
        exit(EXIT_FAILURE);
    }

    text_points.setFont(font);
    text_points.setString("Points:");
    text_points.setCharacterSize(24);
    text_points.setStyle(sf::Text::Regular);

    text_npoints.setFont(font);
    text_npoints.setString("0");
    text_npoints.setCharacterSize(24);
    text_npoints.setStyle(sf::Text::Regular);
    text_npoints.setPosition(text_points.getPosition().x + 80,
                             text_points.getPosition().y);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                printf("[INFO] - Closing window!\n");
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
                printf("[INFO] - Closing window!\n");
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                bullets.push_back(Bullet(spaceship.getTransform().transformPoint(spaceship.getPoint(1)),
                                         spaceship.getRotation()));
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
        window.draw(text_points);
        window.draw(text_npoints);
        window.draw(spaceship);

        for(int i = 0; i < bullets.size(); i++) {
            if(bullets[i].object.getPosition().x > window.getSize().x ||
               bullets[i].object.getPosition().x < 0 ||
               bullets[i].object.getPosition().y > window.getSize().y ||
               bullets[i].object.getPosition().y < 0) {
                bullets.erase(bullets.begin() + i);
            }

            bullets[i].object.move(std::cos(PI * bullets[i].object.getRotation() / 180.f),
                                   std::sin(PI * bullets[i].object.getRotation() / 180.f));
            window.draw(bullets[i].object);
        }

        window.display();
    }
}
