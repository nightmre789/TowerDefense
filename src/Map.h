#include <utility>

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
using namespace sf;

class Map {
    Sprite bg;
    std::function<Vector2f(float)> movement;

public:
    Map(Sprite &bg, std::function<Vector2f(float)> movement)
        : bg(bg)
        , movement(std::move(movement))
    {}
};
