#pragma once
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include "GameList.h"
#include "GameObject.h"
#include <list>


class GameState
{
private:
	GameList<GameObject, true> myList;
	list<EventHandler*> myEvents;
	// Puntero al juego

	void Render() const;
	void Update();
	void HandleEvent(const SDL_Event&);
	void Save(ostream&) const;
	void HasDied(GameList<GameObject, true>::anchor);
	void getGame() const;

	void addEventListener();
	void addObject();

public:

};

