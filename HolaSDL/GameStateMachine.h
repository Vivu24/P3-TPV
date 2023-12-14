#pragma once
#include "GameState.h"
#include <stack>

class GameStateMachine
{
private:
	std::stack<GameState*> myState;

public:
	void Update();
	void Render() const;
	void HandleEvent(const SDL_Event& event);

	void PushState(GameState* state) /*const*/;
	void ReplaceState(GameState* state);
	void PopState();
};

