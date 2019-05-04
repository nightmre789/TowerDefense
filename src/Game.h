#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "engine/StateHandler.h"
#include "engine/AssetHandler.h"
#include "engine/InputHandler.h"
#include "Projectiles.h"
using namespace std;
using namespace sf;

struct GD {
    RenderWindow window;
    StateHandler stateHandler;
    AssetHandler assetHandler;
    InputHandler inputHandler;
};
typedef shared_ptr <GD> pGameData;

class Game {
    const float fps { 60.f };
    const float dt { 1.f / fps};
    Clock gameClock;
    pGameData data = make_shared<GD>();
    void run();

public:
    Game(unsigned width, unsigned height, string title);
};