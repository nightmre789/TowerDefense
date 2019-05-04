#include "StateHandler.h"

void StateHandler::pushState(pState toPush, bool override) {
    this -> push = true;
    this -> override = override;
    this -> toPush = move(toPush);
}

void StateHandler::popState() { this -> pop = true; }

void StateHandler::updateState() {
    if (pop && !states.empty()) {
        states.pop();
        if (!states.empty()) states.top() -> resume();
    } pop = false;

    if (push) {
        if (!states.empty()) {
            if (override) states.pop();
            else states.top() -> pause();
        }
        states.push(move(toPush));
        states.top() -> init();
    } push = false;
}

pState &StateHandler::getActiveState() { return states.top(); }