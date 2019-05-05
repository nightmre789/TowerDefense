#include <utility>

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
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
        Tower(Vector2f position, Sprite sprite, function<bool(void)> fire, int radius, int damage, float fireRate)
            : position(position)
            , fire(std::move(fire))
            , sprite(std::move(sprite))
            , range(radius)
            , damage(damage)
            , fireRate(fireRate)
            , reload(0.f)
            , radius(CircleShape(radius))
        {}
        int range, damage;
        CircleShape radius;
        float fireRate, reload;
        Vector2f position;
        Sprite sprite;
        function<bool(void)> fire;
    };

    vector<Tower> towers;

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &tower : towers)
            target.draw(tower.sprite);
    }

public:
    Towers() = default;

    void addTower(Vector2f position, Sprite &s, const function<bool(void)> &fire, int radius, int damage, float fireRate) {
        s.setOrigin(s.getLocalBounds().width / 2.f, s.getLocalBounds().height / 2.f);
        s.setPosition(position);
        Tower t(position, s, fire, radius, damage, fireRate);
        towers.push_back(t);
    }

    void update(float dt) {
        for (auto &tower : towers) {
            tower.reload += dt;
            if (tower.reload >= tower.fireRate)
                if (tower.fire()) tower.reload = 0;
        }
    }

    static int getRadius(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 70;
            case MOUSE: return 50;
            case FAN: return 200;
            default: return 0;
        }
    }

    static int getDamage(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 50;
            case MOUSE: return 20;
            case FAN: return 15;
            default: return 0;
        }
    }

    static float getFireRate(short unsigned towerType) {
        switch(towerType) {
            case CDKEY: return 7.5;
            case MOUSE: return 2.5;
            case FAN: return 5.5;
            default: return 0;
        }
    }
};