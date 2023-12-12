#pragma once
#include "GameState.h"
#include <stack>

class GameStateMachine
{
private:
	stack<GameState*> myState;

	void PushState(GameState* state) /*const*/;
	void ReplaceSatate(GameState* state);
	void PopState();

	void Update();
	void Render() const;
	void HandleEvent(const SDL_Event& event);
};

