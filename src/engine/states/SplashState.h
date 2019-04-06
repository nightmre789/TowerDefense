#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../../Game.h"

using namespace sf;

class SplashState : public State {
    GameData data;
    Clock clock;
    Sprite bg;
public:
    SplashState(GameData data);

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;
};