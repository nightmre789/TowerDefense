#pragma once

#include "../states/State.h"
#include <memory>
#include <stack>
using namespace std;

typedef unique_ptr<State> pState;

class StateHandler {
    stack<pState> states;
    pState toPush;
    bool push{}, pop{}, override{};
public:
    StateHandler() {};
    ~StateHandler() {};

    void pushState(pState toPush, bool override = true);
    void popState();
    void updateState();

    pState &getActiveState();
};
