#include "StateHandler.h"

void StateHandler::pushState(pState toPush, bool override) {
    this -> push = true;
    this -> override = override;
    this -> toPush = move(toPush);
}

void StateHandler::popState() { this -> pop = true; }

void StateHandler::updateStack() {
    if (pop && !states.empty()) {
        pop = false;
        states.pop();
        if (states.empty()) states.top() -> resume();
    }
    else if (push) {
        push = false;
        if (!states.empty()) {
            if (override) states.pop();
            else states.top() -> pause();
        }
        states.push(move(toPush));
        states.top() -> init();
    }
}

pState &StateHandler::getActiveState() { return states.top(); }