#include <utility>

#include <cmath>
#include <iostream>
#include <string.h>
#include "GameState.h"
#include "../util/Definitions.h"

GameState::GameState(pGameData data) : data(std::move(data)), level(1)
{}

GameState::~GameState() = default;

void GameState::init() {
    map = new Map(new Sprite((data -> assetHandler.getTexture("Map"))), [] (float t) -> Vector2f {
        auto x = static_cast<float> (sqrt(112.5));
        return
            t <= 14.13  ? Vector2f(15 * t, 500) :
            t <= 20     ? Vector2f(212, -15 * t + 712) :
            t <= 41.2   ? Vector2f(x * t, -x * t + 623) :
            t <= 53     ? Vector2f(15 * t - 180, 186) :
            t <= 82.4   ? Vector2f(x * t + 52, x * t - 375) :
            t <= 90     ? Vector2f(15 * t - 310, 500) :
            t <= 120    ? Vector2f(1040, -15 * t + 1850) :
            t <= 160    ? Vector2f(15 * t - 760, 50) :
            Vector2f(1280, 150);
        }, 160
    );

    viruses = new Viruses(map -> movement, map -> complete);

    alpha.setTexture(data -> assetHandler.getTexture("AlphaMap"));
    alphaMap = alpha.getTexture() -> copyToImage();

    towerBar.setTexture(data -> assetHandler.getTexture("TowerBar"));
    towerBar.setPosition(780, 620);

    CDIcon.setTexture(data -> assetHandler.getTexture("CDKey"));
    CDIcon.setOrigin(CDIcon.getLocalBounds().width / 2.f, CDIcon.getLocalBounds().height / 2.f);
    CDIcon.setPosition(874, 667);
    fanIcon.setTexture(data -> assetHandler.getTexture("Fan"));
    fanIcon.setOrigin(fanIcon.getLocalBounds().width / 2.f, fanIcon.getLocalBounds().height / 2.f);
    fanIcon.setPosition(1050, 668);
    mouseIcon.setTexture(data -> assetHandler.getTexture("Mouse"));
    mouseIcon.setOrigin(mouseIcon.getLocalBounds().width / 2.f, mouseIcon.getLocalBounds().height / 2.f);
    mouseIcon.setPosition(956, 668);

    heart.setTexture(data -> assetHandler.getTexture("Heart"));
    heart.setPosition(10, 10);
    life.setFillColor(Color(243, 119, 95));
    life.setPosition(80, 15);
    life.setFont(data -> assetHandler.getFont("Semilight"));
    life.setCharacterSize(36);
    life.setString("200");

    dollar.setTexture(data -> assetHandler.getTexture("Dollar"));
    dollar.setPosition(10, 70);
    cash.setFillColor(Color(239, 199, 88));
    cash.setPosition(80, 75);
    cash.setFont(data -> assetHandler.getFont("Semilight"));
    cash.setCharacterSize(36);
    cash.setString("550");

    gameOver.setCharacterSize(72);
    gameOver.setString("GAME OVER");
    gameOver.setOrigin(gameOver.getGlobalBounds().width / 2.f, gameOver.getGlobalBounds().height / 2.f);
    gameOver.setPosition(640, 360);
    gameOver.setFont(data -> assetHandler.getFont("Semilight"));

    towerSprites[0] = &CDIcon;
    towerSprites[1] = &mouseIcon;
    towerSprites[2] = &fanIcon;
}

void GameState::handleInput() {
    static auto *pSprite = new Sprite();
    static bool drag = false;
    static Vector2f initial;
    static short unsigned i;

    Vector2i mousePos(data -> inputHandler.getMousePos(data -> window));

    Event e {};
    while (data -> window.pollEvent(e))
        switch(e.type) {
            case Event::Closed:
                data -> window.close();
                break;

            case Event::MouseButtonPressed:
                for (i = 0; i < 3; i++) {
                    pSprite = towerSprites[i];
                    if (pSprite -> getGlobalBounds().contains(data -> window.mapPixelToCoords(mousePos))) {
                        drag = true;
                        initial = pSprite -> getPosition();
                        pSprite -> setPosition(Vector2f(mousePos));
                        break;
                    }
                }
                break;

            case Event::MouseButtonReleased:

                if (!alphaMap.getPixel(mousePos.x, mousePos.y).toInteger() && drag) {
                    int radius = Towers::getRadius(i);
                    int damage = Towers::getDamage(i);
                    int pierce = Towers::getPierce(i);
                    int cost = Towers::getCost(i);
                    float fireRate = Towers::getFireRate(i);
                    Sprite s = *pSprite;
                    cout << cost << endl;
                    switch(i) {
                        case CDKEY:
                            if (money >= cost) {
                            towers.addTower(Vector2f(mousePos), s, s,
                                    [=] () -> bool {
                                        CircleShape c(radius);
                                        c.setOrigin(radius, radius);
                                        c.setPosition(Vector2f(mousePos));
                                        float biggest = 0;
                                        bool fired;
                                        Sprite attack (data -> assetHandler.getTexture("CDKeyAttack"));
                                        for (auto &virus : viruses -> viruses) {
                                            if (intersects(c, virus.sprite.getGlobalBounds()))
                                                if (virus.completed > biggest)
                                                    biggest = virus.completed;
                                        }
                                        if (biggest) {
                                            cout << biggest << endl;
                                            fired = true;
                                            projectiles.addProjectile(
                                                    attack,
                                                    Vector2f(mousePos),
                                                    Vector2f(map -> movement(biggest + 10)),
                                                    50, 5, pierce, damage
                                            );
                                        }
                                        return fired;
                                }, radius, damage, fireRate, cost);
                                money -= cost;
                                cash.setString(to_string(money));
                            }
                            break;

                        case MOUSE:
                            if (money >= cost) {
                            towers.addTower(Vector2f(mousePos), s, s,
                                    [=] () -> bool {
                                        Sprite attack(data -> assetHandler.getTexture("MouseAttack"));
                                        projectiles.addProjectile(
                                            attack,
                                            Vector2f(mousePos),
                                            Vector2f(Mouse::getPosition(data -> window)),
                                            100, 10, pierce, damage
                                        );
                                        return true;
                                    }, radius, damage, fireRate, cost);
                                money -= cost;
                                cash.setString(to_string(money));
                            }
                            break;

                        case FAN:
                            if (money >= cost)  {
                                towers.addTower(Vector2f(mousePos), s, s,
                                    [=] () -> bool {
                                        for (int j = 1; j <= 7; j++) {
                                            string text("FanAttack");
                                            text.append(to_string(j));
                                            Sprite attack(data -> assetHandler.getTexture(text));
                                            projectiles.addProjectile(
                                                    attack,
                                                    Vector2f(mousePos),
                                                    Vector2f(Vector2f(mousePos)
                                                    + Vector2f((float) sin(PI_2 / 7 * (j - 1)), (float) cos(PI_2 / 7 * (j - 1)))),
                                                    50, 2, pierce, damage
                                            );
                                        }
                                        return true;
                                    }, radius, damage, fireRate, cost);
                                money -= cost;
                                cash.setString(to_string(money));
                            }
                            break;

                        default: break;
                    }

                    IntRect bounds = static_cast<IntRect> (pSprite -> getGlobalBounds());
                    for (int j = bounds.left - 10; j < bounds.left + bounds.width + 10; j++)
                        for (int k = bounds.top - 10; k < bounds.top + bounds.height + 10; k++)
                            if ((j >= 0 && j <= 1280) && (k >= 0 && k <=720))
                                alphaMap.setPixel(j, k, Color(10, 10, 10, 100));
                }

                if (drag) pSprite -> setPosition(initial);

                drag = false;
                drawRange = false;
                for (i = 0; i < 3; i++) {
                    pSprite = towerSprites[i];
                    if (pSprite -> getGlobalBounds().contains(data -> window.mapPixelToCoords(mousePos))) {
                        cout << "clicked" << endl;
                        break;
                    }
                    else cout << "missed" << endl;
                }
                break;

            case Event::MouseMoved:
                if (drag) {
                    drawRange = true;
                    pSprite -> setPosition(Vector2f(mousePos));
                    range.setRadius(Towers::getRadius(i));
                    range.setFillColor(
                            alphaMap.getPixel(mousePos.x, mousePos.y).toInteger()
                            ? Color(255, 0, 0, 100)
                            : Color(60, 60, 60, 128)
                    );
                    range.setOrigin(Towers::getRadius(i), Towers::getRadius(i));
                    range.setPosition(Vector2f(mousePos));
                }
                break;
            default:
                break;
        }
}

void GameState::update(float dt) {
    float elapsed = clock.getElapsedTime().asSeconds();
    towers.update(dt, data -> inputHandler.getMousePos(data -> window));
    projectiles.update(dt);
    viruses -> update(dt);

    int i = 0, j = 0, ignore;

    for (auto &virus : viruses -> viruses) {
        if (virus.completed > 85) {
            lives -= virus.life;
            life.setString(to_string(lives));
            viruses -> viruses.erase(viruses->viruses.begin() + i);
        }
        for (auto &projectile : projectiles.projectiles) {
            if (projectile.sprite.getGlobalBounds().intersects(virus.sprite.getGlobalBounds())) {
                int pierce = projectile.pierce;
                if (pierce == 1) projectiles.projectiles.erase(projectiles.projectiles.begin() + j);
                else {
                    projectile.pierce--;
                }
                virus.health -= projectile.damage;
                if (virus.health <= 0) {
                    viruses -> viruses.erase(viruses->viruses.begin() + i);
                    money += 5;
                    cash.setString(to_string(money));
                }
            }
            j++;
        } i++;
    }

    static float count = 0;
    static float tCount = 0;
    static float wCount = 0;

    switch(level) {
        case 1:
            if (elapsed < 5) {
                if (count > 7) {
                    count = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Virus")), 1, 50, 1, 2);
                } else count += dt;

            } else if (viruses -> viruses.empty()) {
                level = 2;
                money += 150;
                cash.setString(to_string(money));
                clock.restart();
            }
            break;
        case 2:
            if (elapsed < 20) {
                if (tCount > 7) {
                    tCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Trojan")), 3, 50, 1, 2);
                } else tCount += dt;

                if (wCount > 3) {
                    wCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Widow")), 1,  80, 3, 2);
                } else wCount += dt;

            } else if (viruses -> viruses.empty()) {
                level = 3;
                money += 150;
                cash.setString(to_string(money));
                clock.restart();
            }
            break;
        case 3:
            if (elapsed < 50) {
                if (tCount > 5) {
                    tCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Trojan")), 3, 50, 1, 2);
                } else tCount += dt;

            } else if (viruses -> viruses.empty()) {
                level = 4;
                money += 150;
                cash.setString(to_string(money));
                clock.restart();
            }
            break;
        case 4:
            if (elapsed < 20) {
                if (count > 3) {
                    count = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Virus")), 1, 50, 1, 2);
                } else count += dt;

                if (tCount > 7) {
                    tCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Trojan")), 3, 50, 1, 2);
                } else tCount += dt;

                if (wCount > 10) {
                    wCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Widow")), 1, 80, 2, 4);
                } else wCount += dt;

            } else if (viruses -> viruses.empty()) {
                level = 5;
                money += 150;
                cash.setString(to_string(money));
                clock.restart();
            }
            break;
        case 5:
            if (elapsed < 40) {
                if (wCount > 3) {
                    wCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Widow")), 3, 100, 2, 4);
                } else wCount += dt;

            } else if (viruses -> viruses.empty()) {
                level = 6;
                money += 150;
                cash.setString(to_string(money));
                clock.restart();
            }
            break;
        case 6:
            if (elapsed < 50) {
                if (count > 3) {
                    count = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Virus")), 2, 50, 1, 2);
                } else count += dt;

                if (tCount > 7) {
                    tCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Trojan")), 5, 50, 1, 2);
                } else tCount += dt;

                if (wCount > 10) {
                    wCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Widow")), 2, 500, 2, 4);
                } else wCount += dt;

            } else if (viruses -> viruses.empty()) {
                level = 7;
                money += 150;
                cash.setString(to_string(money));
                clock.restart();
            }
            break;
        case 7:
            if (elapsed < 10) {
                if (wCount > 1) {
                    wCount = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Burney")), 5, 200, 2, 4);
                } else wCount += dt;
            } else if (viruses -> viruses.empty()) {
                level = 7;
                clock.restart();
            }
        default:
            break;
    }
}

void GameState::draw(float dt) {

    data -> window.clear(Color::Black);

    if (lives > 0) {
        data->window.draw(*map);

        data->window.draw(towers);
        data->window.draw(projectiles);

        data->window.draw(*viruses);

        data->window.draw(towerBar);
        data->window.draw(CDIcon);
        data->window.draw(mouseIcon);
        data->window.draw(fanIcon);

        data->window.draw(heart);
        data->window.draw(life);

        data->window.draw(dollar);
        data->window.draw(cash);

        if (drawRange) data->window.draw(range);
    } else data -> window.draw(gameOver);

    data -> window.display();
}
