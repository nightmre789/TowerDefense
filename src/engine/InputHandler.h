#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class InputHandler {

public:
    InputHandler() = default;

    bool isClicked(Sprite sprite, Mouse::Button button, RenderWindow &window);
    Vector2i getMousePos(RenderWindow &window);
};
