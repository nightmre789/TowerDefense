#include "InputHandler.h"

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
    return Mouse::getPosition(window);
}
