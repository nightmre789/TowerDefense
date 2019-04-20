#include "Button.h"

Button::Button(float x, float y, float width, float height, Texture &idle, Texture &hover, Texture &active)
               : idle(idle)
               , hover(hover)
               , active(active)
{
    state = BTN_IDLE;

    shape.setPosition(Vector2f(x, y));
    shape.setSize(Vector2f(width, height));
    shape.setTexture(&idle);
}

const bool Button::isPressed() const { return state == BTN_ACTIVE; }

void Button::draw(RenderTarget &target, RenderStates states) const {
    target.draw(shape);
}

void Button::update(const Vector2f mousePos) {
    state = BTN_IDLE;
    if (shape.getGlobalBounds().contains(mousePos)) {
        state = BTN_HOVER;
        if (Mouse::isButtonPressed(Mouse::Left))
            state = BTN_ACTIVE;
    }

    switch (state) {
        case BTN_IDLE:
            shape.setTexture(&idle);
            break;
        case BTN_HOVER:
            shape.setTexture(&hover);
            break;
        case BTN_ACTIVE:
            shape.setTexture(&active);
            break;
        default:
            shape.setTexture(&idle);
            break;
    }
}