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

    void addProjectile() {
        Vector2f aim;
        Vector2i f = Mouse::getPosition();
        aim.x=Mouse::getPosition().x;
        aim.y=Mouse::getPosition().y - 160.f;
        Vector2f norm;
        std::cout << aim.x << " " << aim.y << endl;
        Vector2f aimDir = aim - Vector2f(0.f, 0.f);
        norm.x = aimDir.x / sqrt(static_cast<float>((pow(aimDir.x, 2) + pow(aimDir.y, 2))));
        norm.y = aimDir.y / sqrt(static_cast<float>((pow(aimDir.x, 2) + pow(aimDir.y, 2))));
        Projectile p(CircleShape(10.f), norm * static_cast<float>(50), seconds(30));
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