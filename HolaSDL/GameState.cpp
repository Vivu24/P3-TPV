#include "GameState.h"
#include "SDLApplication.h"

void GameState::Render() const {};

void GameState::Update() {};

void GameState::HandleEvent(const SDL_Event&) {};

void GameState::Save(ostream&) const {};

void GameState::HasDied(GameList<GameObject, true>::anchor) {};

void GameState::addEventListener() {};

void GameState::addObject(GameObject* obj) {
	myList.push_back(obj);
};

