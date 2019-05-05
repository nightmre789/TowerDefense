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
                    float fireRate = Towers::getFireRate(i);
                    Sprite s = *pSprite;
                    switch(i) {
                        case CDKEY:

                            break;

                        case MOUSE:
                            towers.addTower(Vector2f(mousePos), s, s,
                                    [=] () -> bool {
                                        Sprite attack(data -> assetHandler.getTexture("MouseAttack"));
                                        projectiles.addProjectile(
                                            attack,
                                            Vector2f(mousePos),
                                            Vector2f(Mouse::getPosition(data -> window)),
                                            100, 10
                                        );
                                        return true;
                                    }, radius, damage, fireRate);
                            break;

                        case FAN:
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
                                                    50, 2
                                            );
                                        }
                                        return true;
                                    }, radius, damage, fireRate);
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
    static float count = 0;
    towers.update(dt, data -> inputHandler.getMousePos(data -> window));
    projectiles.update(dt);
    viruses -> update(dt);

    int i = 0, j = 0;

    for (auto &virus : viruses -> viruses) {
        for (auto &projectile : projectiles.projectiles) {
            if (projectile.sprite.getGlobalBounds().intersects(virus.sprite.getGlobalBounds())) {
                projectiles.projectiles.erase(projectiles.projectiles.begin() + j);
                viruses -> viruses.erase(viruses -> viruses.begin() + i);
                cout << "PEW PEW BITCH" << endl;
            } j++;
        } i++;
    }

    switch(level) {
        case 1:
            if (elapsed < 20) {
                if (count > 10) {
                    count = 0;
                    viruses -> addVirus(Sprite(data -> assetHandler.getTexture("Virus")), 13, 100);
                } else count += dt;
            } else level = 2;
            break;
        case 2:
            break;
        default:
            break;
    }
}

void GameState::draw(float dt) {
    float elapsed = clock.getElapsedTime().asSeconds();

    data -> window.clear(Color::Black);

    data -> window.draw(*map);

    data -> window.draw(*towerSprites[0]);

    data -> window.draw(towers);
    data -> window.draw(projectiles);

    data -> window.draw(*viruses);

    data -> window.draw(towerBar);
    data -> window.draw(CDIcon);
    data -> window.draw(mouseIcon);
    data -> window.draw(fanIcon);
    if (drawRange) data -> window.draw(range);

    data -> window.display();
}
