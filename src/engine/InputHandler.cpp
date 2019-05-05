#include "InputHandler.h"
#include "../util/Definitions.h"

bool InputHandler::isClicked(Sprite sprite, Mouse::Button button, RenderWindow &window) {
    if (Mouse::isButtonPressed(button)) {
        const Vector2i pos = static_cast<Vector2i> (sprite.getPosition());
        IntRect dimensions = static_cast<IntRect> (sprite.getGlobalBounds());
        IntRect spriteRect(pos.x, pos.y, dimensions.width, dimensions.height);
        if (spriteRect.contains(Mouse::getPosition(window))) return true;
    }
    return false;
}

Vector2i InputHandler::getMousePos(RenderWindow &window) {
    Vector2i mousePos(Mouse::getPosition(window));
    return {
        mousePos.x > SCREEN_WIDTH ? SCREEN_WIDTH : mousePos.x < 0 ? 0 : mousePos.x,
        mousePos.y > SCREEN_HEIGHT ? SCREEN_HEIGHT : mousePos.y < 0 ? 0 : mousePos.y
    };
}
