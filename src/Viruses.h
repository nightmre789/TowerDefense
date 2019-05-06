#include <utility>

#include <utility>

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

using namespace std;
using namespace sf;

class Viruses : public Drawable, public Transformable {

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &virus : viruses) {
            target.draw(virus.sprite);
        }
    }

    function<Vector2f(float)> movement;

    int complete;
public:

    struct Virus {
        Virus(Sprite sprite, float speed, int health, int life, int cash)
                : sprite(std::move(sprite))
                , speed(speed)
                , health(health)
                , completed(0)
                , life(life)
                , cash(cash)
        {}

        Sprite sprite;
        float speed, completed;
        int health, life, cash;
    };

    vector<Virus> viruses;

    Viruses(function<Vector2f(float)> movement, int complete)
        : movement(std::move(movement))
        , complete(complete)
    {}

    void addVirus(Sprite s, float speed ,int health, int life, int cash) {
//        s.setOrigin(s.getLocalBounds().width / 2.f, s.getLocalBounds().height / 2.f);
        Virus v(std::move(s), speed, health, life, cash);
        viruses.push_back(v);
    }

    void update(float dt) {
        for (auto &virus : viruses) {
            virus.completed += 0.5f * (dt / complete) * 100 * virus.speed;
            virus.sprite.setPosition(movement(virus.completed / 100 * complete));
        }
    }

};