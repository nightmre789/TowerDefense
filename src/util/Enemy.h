//
// Created by AA on 5/4/2019.
//

#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H

#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Tower.h"



using namespace std;
using namespace sf;
class Enemy {
        Vector2f position;
        Clock time;
        int health;
        int speed;
        Vector2f velocity;


public:

    Sprite texture;
    void Hit(int damage){
        health-=damage;
    }

    void setVelocity(Vector2f vel) {
        velocity.x=vel.x*speed;
        velocity.y=vel.y*speed;
    }


//
//    void ChangeDirection(){
//
//    }

};

#endif //TOWERDEFENSE_ENEMY_H
