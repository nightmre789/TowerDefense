#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

class Projectiles : public Drawable, public Transformable {

    struct Projectile {

        Projectile(CircleShape shape, Vector2f velocity, Time lifetime)
            : shape(shape)
            , velocity(velocity)
            , lifetime(lifetime)
        {}

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

    void addProjectile(Vector2f aim, Texture &text) {
        Vector2f aimDir = aim - Vector2f(640,360);
        Vector2f norm = aimDir / sqrt(static_cast<float>(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
        Projectile p(CircleShape(100.f), norm * 50.f, seconds(30));
        p.shape.setTexture(&text);
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