#include <utility>

#include <utility>

#include <iostream>
#include "SplashState.h"

SplashState::SplashState(pGameData data) : data(std::move(data)), particles(2500)
{}

SplashState::~SplashState() {
    delete play;
}

void SplashState::init() {
    data -> assetHandler.loadTexture("SplashBG", "assets/images/bg.png");
    data -> assetHandler.loadTexture("SplashTitle", "assets/images/title.png");
    data -> assetHandler.loadFont("Semilight", "assets/fonts/semilight.ttf");
    data -> assetHandler.loadTexture("PlayButtonIdle", "assets/images/b_playIdle.png");
    data -> assetHandler.loadTexture("PlayButtonHover", "assets/images/b_playHover.png");
    data -> assetHandler.loadTexture("PlayButtonActive", "assets/images/b_playActive.png");

    play = new Button(100, 100, 150, 50,
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
        default:
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
    else play -> update(static_cast<Vector2f> (Mouse::getPosition(data -> window)));
    particles.update(seconds(dt));
}

void SplashState::draw(float dt) {
    float elapsed = clock.getElapsedTime().asSeconds();
    data -> window.clear(Color::Black);
    data -> window.draw(bg);
    if (elapsed > 0.5f) data -> window.draw(particles);
    data -> window.draw(title);
    if (elapsed < 5) data -> window.draw(loading);
    else data -> window.draw(*play);
    data -> window.display();
}
