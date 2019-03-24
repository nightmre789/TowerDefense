#include <SFML/Graphics.hpp>
#include "tween/Tween.h"
#include <cmath>
#include <iostream>

using namespace sf;

int main() {
    RenderWindow win(VideoMode(800, 600), "TweenSF | Example1");

    CircleShape sh(100);
    sh.setFillColor(Color::Black);

    Properties<CircleShape> p1 = sh;
    p1.position += Vector2f(300, 300);
    p1.scale = Vector2f(0.5f, 0.5f);
    p1.fillColor = Color::Red;

    // arguments: object to tween, target properties, duration, easing (default easing::linear)
    Tween<CircleShape> tween(sh, p1, sf::seconds(5), bounceOut);

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

        win.draw(sh);
        win.display();
    }
    /*sf::RenderWindow window(sf::VideoMode(1280, 720), "tower defense woooo yea");
    sf::CircleShape shape(17);
    sf::Vector2f origin(640, 360);
    shape.setFillColor(sf::Color::Cyan);

    sf::Vector2f movement(0.f,0.f);
    float angle = 0;

    while (window.isOpen()) {
        sf::Event event{};

        movement.x = origin.x + std::cos(angle) * 250 - shape.getPosition().x;
        movement.y = origin.y + std::sin(angle) * 250 - shape.getPosition().y;

        shape.move(movement);
        angle += 0.03f;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;*/
}