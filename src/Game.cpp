#include "Game.h"
#include "engine/states/SplashState.h"

Game::Game(unsigned width, unsigned height, string title) {
    data -> window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);
    data -> stateHandler.pushState(pState (new SplashState(data)));
    run();
}

void Game::run() {
    float newTime, frameTime, interpolation, accumulator = 0.0f;
    float currentTime = gameClock.getElapsedTime().asSeconds();
    while (data -> window.isOpen()) {
        data -> stateHandler.updateState();
        newTime = gameClock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime > 0.25f ? 0.25f : newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= fps) {
            data -> stateHandler.getActiveState() -> handleInput();
            data -> stateHandler.getActiveState() -> update(fps);
            accumulator -= fps;
        }
        interpolation = accumulator / fps;
        data -> stateHandler.getActiveState() -> draw (interpolation);
        data -> window.clear(Color::Black);
    }
}
