#include <SFML/Graphics.hpp>
#include "tween/Tween.h"
#include <cmath>
#include <iostream>

using namespace sf;

int main() {
    RenderWindow win(VideoMode(1280, 720), "take 2. we bak boys");

    CircleShape c(100);
    c.setFillColor(Color::Black);

    Properties<CircleShape> p = c;
    p.position += Vector2f(600, 600);
    p.scale = Vector2f(0.25f, 0.25f);
    p.fillColor = Color::Cyan;

    Tween<CircleShape> tween(c, p, sf::seconds(5.25), quintOut);

    Clock timer;

    while(win.isOpen())
    {
        Event e{};
        while(win.pollEvent(e))
        {
            if(e.type == Event::Closed)
                win.close();
        }

        win.clear(Color::White);

        sf::Time delta = timer.restart();
        tween.update(delta); // tween calculates properties and automatically updates target object properties

        win.draw(c);
        win.display();
    }
    /*sf::RenderWindow window(sf::VideoMode(1280, 720), "tower defense woooo yea");
    sf::CircleShape cape(17);
    sf::Vector2f origin(640, 360);
    cape.setFillColor(sf::Color::Cyan);

    sf::Vector2f movement(0.f,0.f);
    float angle = 0;

    while (window.isOpen()) {
        sf::Event event{};

        movement.x = origin.x + std::cos(angle) * 250 - cape.getPosition().x;
        movement.y = origin.y + std::sin(angle) * 250 - cape.getPosition().y;

        cape.move(movement);
        angle += 0.03f;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(cape);
        window.display();
    }
    return 0;*/
}