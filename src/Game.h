#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "engine/StateHandler.h"
#include "engine/AssetHandler.h"
#include "engine/InputHandler.h"
using namespace std;
using namespace sf;

struct GD {
    RenderWindow window;
    StateHandler stateHandler;
    AssetHandler assetHandler;
    InputHandler inputHandler;
};
typedef shared_ptr <GD> GameData;

class Game {
    const float fps = 1.0f / 60.0f;
    Clock gameClock;
    GameData data = make_shared<GD>();
    void run();

public:
    Game(unsigned width, unsigned height, string title);
};