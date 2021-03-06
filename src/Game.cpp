#include "Game.h"
#include "states/SplashState.h"
#include "states/GameState.h"
#include <iostream>

using namespace std;

Game::Game(unsigned width, unsigned height, string const title) {
    data -> window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);
    data -> stateHandler.pushState(pState (new SplashState(data)));
    run();
}

void Game::run() {
    while (data -> window.isOpen()) {
        data -> stateHandler.updateState();

        data -> stateHandler.getActiveState() -> handleInput();
        data -> stateHandler.getActiveState() -> update(dt);

        data -> stateHandler.getActiveState() -> draw (dt);
        data -> window.clear();
    }
}
