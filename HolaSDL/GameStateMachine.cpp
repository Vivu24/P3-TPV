#include "GameStateMachine.h"

void GameStateMachine::PushState(GameState* state) /*const*/ {
	myState.push(state);	
}

void GameStateMachine::ReplaceSatate(GameState* state) {
    if (!myState.empty()) {
        delete myState.top();
        myState.pop();
    }
    myState.push(state);
}

void GameStateMachine::PopState() {
    if (!myState.empty()) {
        delete myState.top();
        myState.pop();
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
