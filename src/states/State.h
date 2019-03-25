#pragma once

class State {
public:
    virtual void init() = 0;

    virtual void inputHandler() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void pause() {}
    virtual void resume() {}
};