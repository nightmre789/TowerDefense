#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Game.h"
#include "../ParticleEmitter.h"
#include "../Projectiles.h"
#include "../Button.h"
#include "../Map.h"

using namespace sf;

class SplashState : public State {
    ParticleEmitter particles;
    Projectiles projectiles;
    pGameData data;
    Clock clock;
    Sprite bg;
    Sprite title;
    Text loading;
    Button *play;
    Map *map;

public:
    SplashState(pGameData data);
    ~SplashState();

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;
};