#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum States {
    BTN_IDLE= 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button : public Drawable, public Transformable {

    short unsigned state;

    RectangleShape shape;
    
    Texture idle, hover, active;

public:
    Button(float x, float y, Texture &idle, Texture &hover, Texture &active);

    const bool isPressed() const;

    bool contains(Vector2f);

    void update(Vector2f mousePos);

private:
    void draw(RenderTarget &target, RenderStates states) const override;
};