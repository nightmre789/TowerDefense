#include <sstream>
#include <iostream>
#include "SplashState.h"

SplashState::SplashState(GameData data) : data(data)
{}

void SplashState::init() {
    data -> assetHandler.loadTexture("Splash", "assets/images/fail.png");
    bg.setTexture(data -> assetHandler.getTexture("Splash"));
}

void SplashState::handleInput() {
    Event e {};
    while (data -> window.pollEvent(e)) {
        if (e.type == Event::Closed) data -> window.close();
    }
}

void SplashState::update(float dt) {
    // if splash done then switch state to menu
    // temporary time for now.
    if (clock.getElapsedTime().asSeconds() > 3) {
        cout << "Go to main menu" << endl;
    }
}

void SplashState::draw(float dt) {
    data -> window.clear(Color::Red);
    data -> window.draw(bg);
    data -> window.display();
}
