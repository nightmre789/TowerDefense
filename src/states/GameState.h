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
    int level, lives = 200, money = 550;
    Sprite *towerSprites[3], alpha, towerBar;
    Sprite CDIcon, fanIcon, mouseIcon;
    Map *map;
    Towers towers;
    Viruses *viruses;
    Projectiles projectiles;
    Image alphaMap;
    CircleShape range;
    Text life, cash;
    Sprite gameOver;
    Sprite heart, dollar;
    Text waveNumber;
    bool finished = false;
    bool drawRange = false;

public:
    GameState(pGameData data);
    ~GameState();

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;

    bool intersects(const CircleShape &c, const FloatRect &fr){
        Vector2f topLeft(fr.left, fr.top);
        Vector2f topRight(fr.left + fr.width, fr.top);
        Vector2f botLeft(fr.left, fr.top + fr.height);
        Vector2f botRight(fr.left + fr.width, fr.top + fr.height);

        return contains(c, topLeft) ||
               contains(c, topRight) ||
               contains(c, botLeft) ||
               contains(c, botRight);
    }

    bool contains(const CircleShape &c, const Vector2f &p){
        Vector2f center = c.getPosition();
        float a = (p.x - center.x);
        float b = (p.y - center.y);
        a *= a;
        b *= b;
        float r = c.getRadius() * c.getRadius();

        return (( a + b ) < r);
    }
};