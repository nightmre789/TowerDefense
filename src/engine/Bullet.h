#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;

class Bullet {
public:
    CircleShape shape;
    float radius;
    Vector2f curVel;
    float maxSpeed;

    Bullet (float radius = 5.f)
        : curVel(1.f,1.f)
        , maxSpeed(15.f)
        , radius(radius)
    {
        this -> shape.setFillColor(Color::Blue);
        this -> shape.setRadius(radius);
    }
};