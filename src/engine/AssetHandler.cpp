#include <iostream>
#include "AssetHandler.h"

void AssetHandler::loadTexture(string name, string fileName) {
    Texture t;
    if (!t.loadFromFile(fileName))
        t.loadFromFile("assets/images/fail.png");
    textures[name] = t;
}

Texture &AssetHandler::getTexture(string name) {
    return textures.at(name);
}

void AssetHandler::loadFont(string name, string fileName) {
    Font f;
    if (!f.loadFromFile(fileName))
        f.loadFromFile("assets/fonts/fail.ttf");
    fonts[name] = f;
}

Font &AssetHandler::getFont(string name) {
    return fonts.at(name);
}