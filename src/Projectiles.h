#include <utility>

#include <utility>

#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>
#include "util/Definitions.h"

using namespace sf;
using namespace std;

class Projectiles : public Drawable, public Transformable {

    struct Projectile {
        Projectile(Sprite sprite, Vector2f velocity, Time lifetime)
                : sprite(std::move(sprite)), velocity(velocity), lifetime(lifetime)
        {}

        Sprite sprite;
        Vector2f velocity;
        Time lifetime;
    };

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &projectile : projectiles)
            target.draw(projectile.sprite);
    }

public:
    vector<Projectile> projectiles;

    Projectiles() = default;

    void addProjectile(Sprite &sprite, Vector2f start, Vector2f end, float speed, float lifetime) {
        Vector2f aim(end - start);
        float rotation = atan2(aim.y, aim.x) * (float) (180 / PI) + 90;
        auto mag = static_cast<float> (sqrt(pow(aim.x, 2) + pow(aim.y, 2)));
        Vector2f unit(aim.x / mag, aim.y  / mag);
        Projectile p(sprite, speed * unit, seconds(lifetime));
        p.sprite.setOrigin(p.sprite.getLocalBounds().width / 2.f, p.sprite.getLocalBounds().height / 2.f);
        p.sprite.setPosition(start);
        p.sprite.setRotation(rotation);
        projectiles.push_back(p);
    }

    void update(float dt) {
        for (int i = 0; i < projectiles.size(); i++) {
            Projectile &p = projectiles[i];

            p.lifetime -= seconds(dt);

            if (p.lifetime <= Time::Zero) {
                projectiles.erase(projectiles.begin() + i);
            }

            p.sprite.setPosition(p.sprite.getPosition() + p.velocity * dt);
        }
    }
};