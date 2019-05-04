//
// Created by AA on 5/1/2019.
//

#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H

#include "../Projectiles.h"
#include "Enemy.h"

class Tower {
        CircleShape radius;
        int damage;
        Sprite tower;
        Vector2f position;
        Sprite sprite;
        Enemy* Focus;

public:
    Projectiles projectiles;
    static int TowNum;
    void AddTower(Vector2f position,Texture TowerTexture,Texture ProjectileTexture,float range,int damage){
        this->position=position;
        this->tower.setTexture(TowerTexture);
        this->projectiles.setPosition(position);
        // set texture for projectile
        radius.setPosition(position);
        radius.setRadius(range);
        this->damage=damage;
        }
    void Fire(Enemy* enemies,int EnNum){
            for(int j = 0;j<EnNum;j++){
                if(Collision::CircleTest(sprite,enemies[EnNum].texture)) Focus=&enemies[EnNum];
            }
        }


    void update(){
//update function
    }

    void draw(){
        //draw function
    }
};
int Tower::TowNum=0;

#endif //TOWERDEFENSE_TOWER_H
