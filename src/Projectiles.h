#include <utility>

#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>
#include "util/Collision.h"


using namespace sf;
using namespace std;

class Projectiles : public Drawable, public Transformable {

    void draw(RenderTarget &target, RenderStates states) const override {
        for (const auto &projectile : projectiles)
            target.draw(projectile.shape);
    }

public:
    Projectiles() = default;

    struct Projectile {

        Projectile(Sprite shape, Vector2f velocity, Time lifetime)
                : shape(std::move(shape)), velocity(velocity), lifetime(lifetime) {}

        Sprite shape;
        Vector2f velocity;
        Time lifetime;
    };

    vector<Projectile> projectiles;

    void addProjectile(Vector2i mouse,Vector2i position) {
        Vector2f unit;
        unit.x=mouse.x - position.x/ (sqrt(pow(mouse.x,2)+pow(mouse.y,2)));
        unit.y=mouse.y - position.y/ (sqrt(pow(mouse.x,2)+pow(mouse.y,2)));
//        Projectile p(Sprite shape,Vector2f unit,Time as);
//        projectiles.push_back(p);  //fix this part
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
    void draw(RenderTarget &target, RenderStates states){
        for(int i=0;i<projectiles.size();i++){
            //
        }
    }
};