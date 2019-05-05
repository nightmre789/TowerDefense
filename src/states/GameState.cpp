#include <utility>

#include <cmath>
#include <iostream>
#include "GameState.h"
#include "GameState.h"
#include "../util/Definitions.h"
#include "../Towers.h"

GameState::GameState(pGameData data) : data(std::move(data))
{}

GameState::~GameState() = default;

void GameState::init() {
    Sprite tower(data -> assetHandler.getTexture("CDKey"));
    towers.addTower(tower, Vector2f(500, 200),
            [=] () -> bool {
                Sprite attack(data -> assetHandler.getTexture("CDKeyAttack"));
                projectiles.addProjectile(
                        attack,
                        Vector2f(500, 200),
                        Vector2f(Mouse::getPosition(data -> window)),
                        50, 10
                        );
                return true;
            },
            300, 400, 7
    );
    virus.setTexture(data -> assetHandler.getTexture("Virus"));

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
    alphaMap = data -> assetHandler.getTexture("AlphaMap").copyToImage();
}

void GameState::handleInput() {
    static auto *pSprite = new Sprite();
    static bool drag = false;
    Vector2f initial;

    Event e {};
    while (data -> window.pollEvent(e))
        switch(e.type) {
            case Event::Closed:
                data -> window.close();
                break;
            case Event::MouseButtonPressed:
                if (virus.getGlobalBounds().contains(data -> window.mapPixelToCoords(Mouse::getPosition(data -> window)))) {
                    drag = true;
                    pSprite = &virus;
                    initial = Vector2f(Mouse::getPosition(data -> window));
                    pSprite -> setPosition(Vector2f(Mouse::getPosition(data -> window)) - Vector2f(35.f, 35.f));
                }
                break;
            case Event::MouseButtonReleased:
                drag = false;
                if (virus.getGlobalBounds().contains(data -> window.mapPixelToCoords(Mouse::getPosition(data -> window)))) {
                    cout << "clicked" << endl;
                }
                else cout << "missed" << endl;
                pSprite -> setPosition(initial);
                break;
            case Event::MouseMoved:
                if (drag) {
                    pSprite -> setPosition(Vector2f(Mouse::getPosition(data -> window)) - Vector2f(35.f, 35.f));
                    cout << alphaMap.getPixel(Mouse::getPosition(data -> window).x, Mouse::getPosition(data -> window).y).toInteger() << endl;
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
    data -> window.draw(virus);

    data -> window.draw(towers);
    data -> window.draw(projectiles);

    data -> window.display();
}
