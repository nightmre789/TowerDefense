#include <utility>

#include <cmath>
#include <iostream>
#include "GameState.h"
#include "../util/Definitions.h"

GameState::GameState(pGameData data) : data(std::move(data))
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
    });

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
                if (drag) pSprite -> setPosition(initial);
                if (!alphaMap.getPixel(mousePos.x, mousePos.y).toInteger() && drag) {
                    int radius = Towers::getRadius(i);
                    int damage = Towers::getDamage(i);
                    float fireRate = Towers::getFireRate(i);
                    Sprite s = *pSprite;
                    IntRect bounds = static_cast<IntRect> (pSprite -> getLocalBounds());
                    switch(i) {
                        case MOUSE:
                            for (int j = bounds.left; j < bounds.width; j++)
                                for (int k = bounds.top; k < bounds.height; k++)
                                    alphaMap.setPixel(j, k, Color(10, 10, 10, 255));
                            towers.addTower(Vector2f(mousePos), s, [=] () -> bool {
                                Sprite attack(data -> assetHandler.getTexture("MouseAttack"));
                                projectiles.addProjectile(
                                        attack,
                                        Vector2f(mousePos),
                                        Vector2f(Mouse::getPosition(data -> window)),
                                        100, 10
                                );
                                return true;
                            }, radius, damage, fireRate);
                        default: break;
                    }
                }
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
                    cout << i << endl;
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
    float elapsed = clock.getElapsedTime().asMilliseconds();
    towers.update(dt);
    projectiles.update(dt);
//    virus.setPosition(map -> movement(clock.getElapsedTime().asSeconds() * 5));
}

void GameState::draw(float dt) {
    float elapsed = clock.getElapsedTime().asSeconds();

    data -> window.clear(Color::Black);

    data -> window.draw(*map);

    data -> window.draw(*towerSprites[0]);

    data -> window.draw(towers);
    data -> window.draw(projectiles);

    data -> window.draw(towerBar);
    data -> window.draw(CDIcon);
    data -> window.draw(mouseIcon);
    data -> window.draw(fanIcon);
    if (drawRange) data -> window.draw(range);

    data -> window.display();
}
