#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Viruses {
    struct Virus {
        Sprite sprite;
        float speed, health, completed;
    };
};