#include <utility>

#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>
#include "util/Collision.h"


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

    void addProjectile(Vector2i screen,Vector2i mouse){
        Vector2f norm;
        Vector2f aim;
        aim.x=mouse.x-screen.x;
        aim.y=mouse.y-screen.y;
        std::cout << aim.x << " " << aim.y << endl;
        norm.x = aim.x / sqrt(static_cast<float>((pow(aim.x, 2) + pow(aim.y, 2))));
        norm.y = aim.y / sqrt(static_cast<float>((pow(aim.x, 2) + pow(aim.y, 2))));
        Projectile p(CircleShape(10.f), norm * static_cast<float>(70), seconds(30));
        projectiles.push_back(p);
    }

    void update(Time dt,RectangleShape& rectShape) {
        for (int i = 0; i < projectiles.size(); i++) {
            Projectile &p = projectiles[i];

            p.lifetime -= dt;

            if (p.lifetime <= Time::Zero) {
                projectiles.erase(projectiles.begin() + i);
            }

            p.shape.setPosition(p.shape.getPosition() + p.velocity * dt.asSeconds());
            if(projectiles[i].shape.getGlobalBounds().intersects(rectShape.getGlobalBounds())){
                p.lifetime=Time::Zero;
                rectShape.setFillColor(Color::Red);
                cout<<"COLLIDED"<<endl;
            }
        }
    }
};