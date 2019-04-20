#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Game.h"
#include "../ParticleEmitter.h"
#include "../Projectiles.h"

using namespace sf;

class SplashState : public State {
    ParticleEmitter particles;
    Projectiles projectiles;
    pGameData data;
    Clock clock;
    Sprite bg;
    Sprite title;
    Text loading;
    Sprite play;

public:
    SplashState(pGameData data);

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;
};