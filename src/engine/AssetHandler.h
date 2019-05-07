#pragma once
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class AssetHandler {
    map<string, Texture> textures;
    map<string, Font> fonts;
    map<int, float> floats;

public:
    AssetHandler() = default;

    void loadTexture(string name, string fileName);
    Texture &getTexture(string name);

    void loadFont(string name, string fileName);
    Font &getFont(string name);
};