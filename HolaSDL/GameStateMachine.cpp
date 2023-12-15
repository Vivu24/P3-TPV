#include "GameStateMachine.h"

void GameStateMachine::PushState(GameState* state) {
	myState.push(state);	
    myState.top()->onEnter();
}

void GameStateMachine::ReplaceState(GameState* state) {
    if (!myState.empty()) {
        if (myState.top()->getStateID() == state->getStateID()) return;

        if (myState.top()->onExit()) {
            delete myState.top();
            myState.pop();
        }
    }

    myState.push(state);
    myState.top()->onEnter();
}

void GameStateMachine::PopState() {
    if (!myState.empty()) {
        if (myState.top()->onExit()) {
            delete myState.top();
            myState.pop();
        }
    }
}

void GameStateMachine::Update() {
    if (!myState.empty()) {
        myState.top()->Update();
    }
}

void GameStateMachine::Render() const {
    if (!myState.empty()) {
        myState.top()->Render();
    }
}

void GameStateMachine::HandleEvent(const SDL_Event& event) {
    if (!myState.empty()) {
        myState.top()->HandleEvent(event);
    }
}
