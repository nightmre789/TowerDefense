#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "../ParticleEmitter.h"
#include "../Projectiles.h"
#include "../Button.h"
#include "../Map.h"
#include "../Towers.h"
#include "../Viruses.h"

using namespace sf;

class GameState : public State {
    pGameData data;
    Clock clock;
    int level;
    Sprite *towerSprites[3], alpha, towerBar;
    Sprite CDIcon, fanIcon, mouseIcon;
    Map *map;
    Towers towers;
    Viruses *viruses;
    Projectiles projectiles;
    Image alphaMap;
    CircleShape range;
    bool drawRange = false;

public:
    GameState(pGameData data);
    ~GameState();

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;
};