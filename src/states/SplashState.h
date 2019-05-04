#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Game.h"
#include "../ParticleEmitter.h"
#include "../Button.h"
#include "../util/Tower.h"


using namespace sf;

class SplashState : public State {
    ParticleEmitter particles;
    Tower towers[5];
    pGameData data;
    Clock clock;
    Sprite bg;
    Sprite title;
    Text loading;
    Button *play;
    RectangleShape rectShape;
    Enemy enemies[5];
    bool col;

public:
    SplashState(pGameData data);
    ~SplashState();

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;
};