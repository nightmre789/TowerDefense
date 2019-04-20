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

    void addProjectile(int a,int b) {
        Vector2f screen;
        screen.x=a*1.5;
        screen.y=b*1.25;
        Vector2f norm;
        Vector2f aim;
        aim.y = Mouse::getPosition().y-screen.y - 5.f;
        aim.x = Mouse::getPosition().x-screen.x - 10.f;
        std::cout << aim.x << " " << aim.y << endl;
        norm.x = aim.x / sqrt(static_cast<float>((pow(aim.x, 2) + pow(aim.y, 2))));
        norm.y = aim.y / sqrt(static_cast<float>((pow(aim.x, 2) + pow(aim.y, 2))));
        Projectile p(CircleShape(10.f), norm * static_cast<float>(70), seconds(30));
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