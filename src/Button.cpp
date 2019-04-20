#include "Button.h"

Button::Button(float x, float y, Texture &idle, Texture &hover, Texture &active)
               : idle(idle)
               , hover(hover)
               , active(active)
{
    state = BTN_IDLE;

    shape.setPosition(Vector2f(x, y));
    shape.setSize(Vector2f(idle.getSize()));
    shape.setTexture(&idle);
}

const bool Button::isPressed() const { return state == BTN_ACTIVE; }

bool Button::contains(const Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::draw(RenderTarget &target, RenderStates states) const {
    target.draw(shape);
}

void Button::update(const Vector2f mousePos) {
    state = BTN_IDLE;
    shape.setTexture(&idle);
    if (shape.getGlobalBounds().contains(mousePos)) {
        state = BTN_HOVER;
        shape.setTexture(&hover);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            state = BTN_ACTIVE;
            shape.setTexture(&active);
        }
    }
}