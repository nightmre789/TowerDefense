#include <utility>

#include <sstream>
#include <iostream>
#include "SplashState.h"

SplashState::SplashState(pGameData data) : data(std::move(data)), particles(100000)
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
    particles.setEmitter(data -> window.mapPixelToCoords(Mouse::getPosition(data -> window)));
    particles.update(seconds(dt));
    if (clock.getElapsedTime().asSeconds() > 3) {
        cout << "Go to main menu" << endl;
    }
}

void SplashState::draw(float dt) {
    data -> window.clear();
    data -> window.draw(particles);
    data -> window.display();
}
