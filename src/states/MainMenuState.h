#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Game.h"

class MainMenuState : public State {

    MainMenuState(pGameData data);
    void init();
    void handleInput();
    void update(float dt);
    void draw(float dt);


};