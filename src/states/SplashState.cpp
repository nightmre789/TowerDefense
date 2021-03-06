#include <utility>

#include <cmath>
#include <iostream>
#include "SplashState.h"
#include "GameState.h"
#include "../util/Definitions.h"

SplashState::SplashState(pGameData data) : data(std::move(data)), particles(2500)
{}

SplashState::~SplashState() {
    cout << "deleting";
    delete play;
}

void SplashState::init() {
    data -> assetHandler.loadTexture("SplashBG", "assets/images/bg.png");
    data -> assetHandler.loadTexture("SplashTitle", "assets/images/title.png");
    data -> assetHandler.loadFont("Semilight", "assets/fonts/semilight.ttf");
    data -> assetHandler.loadTexture("PlayButtonIdle", "assets/images/b_playIdle.png");
    data -> assetHandler.loadTexture("PlayButtonHover", "assets/images/b_playHover.png");
    data -> assetHandler.loadTexture("PlayButtonActive", "assets/images/b_playActive.png");
    data -> assetHandler.loadTexture("Burney", "assets/images/burney.png");

    // gamestate assets
    data -> assetHandler.loadTexture("Map", "assets/images/map.png");
    data -> assetHandler.loadTexture("AlphaMap", "assets/images/alpha.png");

    data -> assetHandler.loadTexture("Virus", "assets/images/virus.png");
    data -> assetHandler.loadTexture("Trojan", "assets/images/trojan.png");
    data -> assetHandler.loadTexture("Widow", "assets/images/widow.png");

    data -> assetHandler.loadTexture("TowerBar", "assets/images/towerBar.png");
    data -> assetHandler.loadTexture("CDKey", "assets/images/cdkey.png");
    data -> assetHandler.loadTexture("CDKeyAttack", "assets/images/cdkeyAttack.png");
    data -> assetHandler.loadTexture("Fan", "assets/images/fan.png");
    data -> assetHandler.loadTexture("FanAttack1", "assets/images/fanAttack1.png");
    data -> assetHandler.loadTexture("FanAttack2", "assets/images/fanAttack2.png");
    data -> assetHandler.loadTexture("FanAttack3", "assets/images/fanAttack3.png");
    data -> assetHandler.loadTexture("FanAttack4", "assets/images/fanAttack4.png");
    data -> assetHandler.loadTexture("FanAttack5", "assets/images/fanAttack5.png");
    data -> assetHandler.loadTexture("FanAttack6", "assets/images/fanAttack6.png");
    data -> assetHandler.loadTexture("FanAttack7", "assets/images/fanAttack7.png");
    data -> assetHandler.loadTexture("FanReload", "assets/images/fanReload.png");
    data -> assetHandler.loadTexture("Mouse", "assets/images/mouse.png");
    data -> assetHandler.loadTexture("MouseAttack", "assets/images/mouseAttack.png");

    data -> assetHandler.loadTexture("Heart", "assets/images/heart.png");
    data -> assetHandler.loadTexture("Dollar", "assets/images/dollar.png");
    data -> assetHandler.loadTexture("GameOver", "assets/images/gameOver.png");

    play = new Button(SCREEN_WIDTH / 2.f - 59, 550,
            data -> assetHandler.getTexture("PlayButtonIdle"),
            data -> assetHandler.getTexture("PlayButtonHover"),
            data -> assetHandler.getTexture("PlayButtonActive")
            );

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
            if (play -> contains(data -> window.mapPixelToCoords(Mouse::getPosition(data -> window))))
                data -> stateHandler.pushState(pState(new GameState(data)), true);
            break;
    }
}

void SplashState::update(float dt) {
    float elapsed = clock.getElapsedTime().asMilliseconds();
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
    projectiles.update(dt);
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
    data -> window.display();
}
