#pragma once

#include <SFML/Graphics.hpp>

#include <utility>
#include <functional>
#include <cmath>
#include "util/Definitions.h"
#include "Game.h"

using namespace std;
using namespace sf;

enum towerTypes {
    CDKEY = 0,
    MOUSE = 1,
    FAN = 2
};

class Towers : public Drawable, public Transformable {

    struct Tower {
        Tower(Vector2f position, Sprite sprite, Sprite reload, function<bool(void)> fire, int radius, int damage, float fireRate, int cost)
            : position(position)
            , fire(std::move(fire))
            , sprite(std::move(sprite))
            , reloadSprite(std::move(reload))
            , range(radius)
            , damage(damage)
            , fireRate(fireRate)
            , reload(0.f)
            , radius(CircleShape(radius))
            , cost(cost)
        {}

        int range, damage, cost;
        CircleShape radius;
        float fireRate, reload;
        Vector2f position;
        Sprite sprite, reloadSprite;
        function<bool(void)> fire;
    };

    vector<Tower> towers;

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &tower : towers) {
            if (tower.reload <= tower.fireRate) target.draw(tower.reloadSprite);
            else target.draw(tower.sprite);
        }
    }

public:
    Towers() = default;

    void addTower(Vector2f position, Sprite &s, Sprite reload, const function<bool(void)> &fire, int radius, int damage, float fireRate, int cost) {
        s.setOrigin(s.getLocalBounds().width / 2.f, s.getLocalBounds().height / 2.f);
        s.setPosition(position);
        reload.setOrigin(s.getLocalBounds().width / 2.f, s.getLocalBounds().height / 2.f);
        reload.setPosition(position);
        Tower t(position, s, std::move(reload), fire, radius, damage, fireRate, cost);
        towers.push_back(t);
    }

    void update(float dt, Vector2i mousePos) {
        for (auto &tower : towers) {
            tower.reload += dt;
            if (tower.reload >= tower.fireRate)
                if (tower.fire()) tower.reload = 0;
            if (tower.range == 50) { // mouse
                Vector2f aim(Vector2f(mousePos) - tower.position);
                float rotation = atan2(aim.y, aim.x) * (float) (180 / PI) + 90;
                tower.sprite.setRotation(rotation);
                tower.reloadSprite.setRotation(rotation);
            }
        }
    }

    static int getCost(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 200;
            case MOUSE: return 400;
            case FAN: return 550;
            default: return 1;
        }
    }

    static int getPierce(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 1;
            case MOUSE: return 1;
            case FAN: return 1;
            default: return 1;
        }
    }

    static int getRadius(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 150;
            case MOUSE: return 50;
            case FAN: return 100;
            default: return 50;
        }
    }

    static int getDamage(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 80;
            case MOUSE: return 20;
            case FAN: return 15;
            default: return 15;
        }
    }

    static float getFireRate(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 7.5;
            case MOUSE: return 2.5;
            case FAN: return 5.5;
            default: return 10;
        }
    }
};