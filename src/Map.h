#include <utility>
#include <SFML/Graphics.hpp>

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
using namespace sf;
using namespace std;

class Map : public Drawable {
    Sprite bg;

    void draw(RenderTarget &target, RenderStates states) const override {
            target.draw(bg);
    }

public:
    int complete;
    function<Vector2f(float)> movement;

    Map(Sprite *bg, function<Vector2f(float)> movement, int complete)
        : bg(std::move(*bg))
        , movement(std::move(movement))
        , complete(complete)
    {}
};
