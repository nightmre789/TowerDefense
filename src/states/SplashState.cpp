#include <utility>

#include <cmath>
#include <iostream>
#include "SplashState.h"
#include "../util/Definitions.h"

SplashState::SplashState(pGameData data) : data(std::move(data)), particles(2500)
{}

SplashState::~SplashState() {
    delete play;
}

void SplashState::init() {
    data -> assetHandler.loadTexture("SplashBG", "assets/images/map.png");
    data -> assetHandler.loadTexture("SplashTitle", "assets/images/title.png");
    data -> assetHandler.loadFont("Semilight", "assets/fonts/semilight.ttf");
    data -> assetHandler.loadTexture("PlayButtonIdle", "assets/images/b_playIdle.png");
    data -> assetHandler.loadTexture("PlayButtonHover", "assets/images/b_playHover.png");
    data -> assetHandler.loadTexture("PlayButtonActive", "assets/images/b_playActive.png");
    data -> assetHandler.loadTexture("Virus", "assets/images/virus.png");

    play = new Button(SCREEN_WIDTH / 2.f - 59, 550,
            data -> assetHandler.getTexture("PlayButtonIdle"),
            data -> assetHandler.getTexture("PlayButtonHover"),
            data -> assetHandler.getTexture("PlayButtonActive")
            );

    data -> map = new Map(bg, [=] (float t) mutable -> Vector2f {
        auto x = static_cast<float> (sqrt(112.5));
        return
            t <= 14.13 ? Vector2f(15 * t, 500) :
            t <= 20 ? Vector2f(212, -15 * t + 712) :
            t <= 41.2 ? Vector2f(x * t, -x * t + 623) :
            t <= 53 ? Vector2f(15 * t - 180, 186) :
            t <= 82.4 ? Vector2f(x * t + 52, x * t - 375) :
            t <= 90 ? Vector2f(15 * t - 310, 500) :
            t <= 120 ? Vector2f(1040, -15 * t + 1850) :
            t <= 160 ? Vector2f (15 * t - 760, 50) :
            Vector2f(1280, 150);
    });

    test.setTexture(data -> assetHandler.getTexture("Virus"));
    bg.setTexture(data -> assetHandler.getTexture("SplashBG"));
    title.setTexture(data -> assetHandler.getTexture("SplashTitle"));

    loading.setFont(data -> assetHandler.getFont("Semilight"));
    loading.setCharacterSize(26);
    loading.setPosition(552, 552);
}

void SplashState::handleInput() {
    Event e {};
    while (data -> window.pollEvent(e))
    switch(e.type) {
        case Event::Closed:
            data -> window.close();
            break;
        case Event::MouseButtonReleased:
            projectiles.addProjectile(Mouse::getPosition(data -> window), 150.f);
            if (play -> contains(data -> window.mapPixelToCoords(Mouse::getPosition(data -> window))))
                cout << "released" << endl;
            break;
        default:
            break;
    }
}

void SplashState::update(float dt) {
    float elapsed = clock.getElapsedTime().asMilliseconds();
    float moveTime = clock.getElapsedTime().asSeconds() * 5;
    int state = (int) (elapsed / 200) % 4;
    if (elapsed < 5000)
        loading.setString(
                state == 0 ? "Loading assets" :
                state == 1 ? "Loading assets." :
                state == 2 ? "Loading assets.." :
                "Loading assets..."
                );
    else play -> update(data -> window.mapPixelToCoords((Mouse::getPosition(data -> window))));
    particles.update(seconds(dt));
    projectiles.update(seconds(dt));
    test.setPosition(data -> map -> movement(moveTime));
}

void SplashState::draw(float dt) {
    float elapsed = clock.getElapsedTime().asSeconds();
    data -> window.clear(Color::Black);
    data -> window.draw(bg);
    if (elapsed > 0.5f) data -> window.draw(particles);
    data -> window.draw(title);
    if (elapsed < 5) data -> window.draw(loading);
    else data -> window.draw(*play);
    data -> window.draw(projectiles);
    data -> window.draw(test);
    data -> window.display();
}
