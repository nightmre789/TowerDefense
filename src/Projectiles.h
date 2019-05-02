#include <utility>

#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>


using namespace sf;
using namespace std;

class Projectiles : public Drawable, public Transformable {

    struct Projectile {

        Projectile(CircleShape shape, Vector2f velocity, Time lifetime)
                : shape(std::move(shape)), velocity(velocity), lifetime(lifetime) {}

        CircleShape shape;
        Vector2f velocity;
        Time lifetime;
    };

    vector<Projectile> projectiles;

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &projectile : projectiles)
            target.draw(projectile.shape);
    }

public:
    Projectiles() = default;

    void addProjectile(Vector2i mousePos, float speed) {
        auto mag = static_cast<float> (sqrt(pow(mousePos.x, 2) + pow(mousePos.y, 2)));
        Vector2f unit(Vector2f(mousePos) / mag);
        Projectile p(CircleShape(10.f), speed * unit, seconds(10));
        projectiles.push_back(p);
    }

    void update(Time dt) {
        for (int i = 0; i < projectiles.size(); i++) {
            Projectile &p = projectiles[i];

            p.lifetime -= dt;

            if (p.lifetime <= Time::Zero) {
                projectiles.erase(projectiles.begin() + i);
            }

            p.shape.setPosition(p.shape.getPosition() + p.velocity * dt.asSeconds());
        }
    }
};