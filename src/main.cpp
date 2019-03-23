#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "tower defense woooo yea");
    sf::CircleShape shape(17);
    sf::Vector2f origin(640, 360);
    shape.setFillColor(sf::Color::Magenta);

    sf::Vector2f movement(0.f,0.f);
    float angle = 0;

    while (window.isOpen()) {
        sf::Event event {};

        movement.x = origin.x + std::cos(angle) * 250 - shape.getPosition().x;
        movement.y = origin.y + std::sin(angle) * 250 - shape.getPosition().y;

        shape.move(movement);
        angle += 0.005f;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}