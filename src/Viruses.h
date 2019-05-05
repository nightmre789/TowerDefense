#include <utility>

#include <utility>

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

using namespace std;
using namespace sf;

class Viruses : public Drawable, public Transformable {

    struct Virus {
        Virus(Sprite sprite, float speed, int health)
            : sprite(std::move(sprite))
            , speed(speed)
            , health(health)
            , completed(0)
        {}

        Sprite sprite;
        float speed, completed;
        int health;
    };

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &virus : viruses) {
            target.draw(virus.sprite);
        }
    }

    function<Vector2f(float)> movement;
    int complete;

public:
    vector<Virus> viruses;

    Viruses(function<Vector2f(float)> movement, int complete)
        : movement(std::move(movement))
        , complete(complete)
    {}

    void addVirus(Sprite s, float speed ,int health) {
//        s.setOrigin(s.getLocalBounds().width / 2.f, s.getLocalBounds().height / 2.f);
        Virus v(std::move(s), speed, health);
        viruses.push_back(v);
    }

    void update(float dt) {
        for (auto &virus : viruses) {
            virus.completed += 0.5f * (dt / complete) * 100;
            virus.sprite.setPosition(movement(virus.completed / 100 * complete));
        }
    }

};