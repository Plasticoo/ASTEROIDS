#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

#define FRAMERATE 60
#define BULLET_SPEED 2.0f
#define ASTEROID_SPEED 1.0f
#define ROTATION_SPEED 1.5f

#define PI 3.14159265f

sf::Vector2f random_asteroid_position(int win_x, int win_y) {
    int _x = (rand() % win_x) + 1;
    int _y = (rand() % win_y) + 1;

    sf::Vector2f v_array[4] = {sf::Vector2f(_x, 0),
                               sf::Vector2f(0, _y),
                               sf::Vector2f(_x, win_y),
                               sf::Vector2f(win_x, _y),
    };

    return v_array[rand()%4];
}

sf::Vector2f normalize(const sf::Vector2f& v) {
    float _s = sqrt(v.x * v.x + v.y * v.y);
    float _x = v.x / _s;
    float _y = v.y / _s;

    return sf::Vector2f(_x, _y);
};

int main(int argc, char** argv) {

    srand(time(NULL));

    bool focus = true;
    bool can_shoot = true;
    bool game_over = false;

    int points = 0;

    // font and text
    sf::Font font;
    sf::Text text_points;
    sf::Text text_npoints;

    // timers
    sf::Clock asteroid_clock;
    int asteroid_time;

    sf::RenderWindow window;
    sf::ConvexShape spaceship;

    // bullets
    std::vector<sf::RectangleShape> bullets;
    std::vector<sf::RectangleShape> asteroids;

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
    spaceship.setFillColor(sf::Color::Black);
    spaceship.setOutlineThickness(1.0f);
    spaceship.setOutlineColor(sf::Color::White);
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

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    can_shoot = true;
                }
            }
        }

        if(game_over) {

            sf::Text text_exit;

            text_exit.setFont(font);
            text_exit.setString("GAME OVER!");
            text_exit.setCharacterSize(64);
            text_exit.setStyle(sf::Text::Regular);
            text_exit.setOrigin(text_exit.getLocalBounds().left + text_exit.getLocalBounds().width/2.0f,
                                text_exit.getLocalBounds().top  + text_exit.getLocalBounds().height/2.0f);
            text_exit.setPosition(window.getSize().x / 2, window.getSize().y / 2);

            if (focus) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    printf("[INFO] - Closing window!\n");
                    window.close();
                }
            }

            window.draw(text_exit);
            window.display();

            continue;
        }

        if (focus) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                printf("[INFO] - Closing window!\n");
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (can_shoot) {
                    sf::RectangleShape bullet(sf::Vector2f(10, 10));
                    bullet.setOrigin(5,5);
                    bullet.setFillColor(sf::Color::Black);
                    bullet.setOutlineThickness(1.0f);
                    bullet.setOutlineColor(sf::Color::Cyan);
                    bullet.setPosition(spaceship.getTransform().transformPoint(spaceship.getPoint(1)));
                    bullet.setRotation(spaceship.getRotation());

                    bullets.push_back(bullet);
                    can_shoot = false;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                spaceship.setRotation(spaceship.getRotation() - ROTATION_SPEED);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                spaceship.setRotation(spaceship.getRotation() + ROTATION_SPEED);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                // TODO: take care of window borders
                spaceship.move(std::cos(PI * spaceship.getRotation() / 180.f),
                               std::sin(PI * spaceship.getRotation() / 180.f));
            }
        }

        // set text
        text_npoints.setString(std::to_string(points));

        // asteroid timings
        asteroid_time = asteroid_clock.getElapsedTime().asSeconds();
        if (asteroid_time > 1) {
            sf::Vector2f rand_vector2f = random_asteroid_position(window.getSize().x, window.getSize().y);

            sf::RectangleShape asteroid(sf::Vector2f(10, 10));
            asteroid.setOrigin(5, 5);
            asteroid.setPosition(rand_vector2f);

            asteroids.push_back(asteroid);

            asteroid_clock.restart();
        }

        window.clear(sf::Color::Black);

        // draw here
        window.draw(spaceship);

        for(int i = 0; (unsigned)i < bullets.size(); i++) {
            if(bullets[i].getPosition().x > window.getSize().x ||
               bullets[i].getPosition().x < 0 ||
               bullets[i].getPosition().y > window.getSize().y ||
               bullets[i].getPosition().y < 0) {
                bullets.erase(bullets.begin() + i);
                continue;
            }

            sf::Vector2f direction(std::cos(PI * bullets[i].getRotation() / 180.f),
                                   std::sin(PI * bullets[i].getRotation() / 180.f));

            bullets[i].move(direction * BULLET_SPEED);
            window.draw(bullets[i]);
        }

        for(int i = 0; (unsigned)i < asteroids.size(); i++) {
            if(asteroids[i].getPosition().x > window.getSize().x ||
               asteroids[i].getPosition().x < 0 ||
               asteroids[i].getPosition().y > window.getSize().y ||
               asteroids[i].getPosition().y < 0) {
                asteroids.erase(asteroids.begin() + i);
                continue;
            }

            for (int j = 0; (unsigned)j < bullets.size(); j++) {
                if (bullets[j].getGlobalBounds().intersects(asteroids[i].getGlobalBounds())) {
                    asteroids.erase(asteroids.begin() + i);
                    bullets.erase(bullets.begin() + j);

                    points++;
                }
            }

            if (asteroids[i].getGlobalBounds().intersects(spaceship.getGlobalBounds())) {
                game_over = true;
            }

            sf::Vector2f direction = normalize(spaceship.getPosition() - asteroids[i].getPosition());

            asteroids[i].move(direction * ASTEROID_SPEED);
            window.draw(asteroids[i]);
        }

        window.draw(text_points);
        window.draw(text_npoints);

        window.display();
    }
}
