#pragma once
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include "GameList.h"
#include "GameObject.h"
#include <list>
#include "EventHandler.h"

class SDLApplication;

class GameState
{
protected:
	GameList<GameObject, true> myList;
	list<EventHandler*> myEvents;
	// Puntero al juego

	virtual void Render() const;
	void Update();
	void HandleEvent(const SDL_Event&);
	void Save(ostream&) const;
	void HasDied(GameList<GameObject, true>::anchor);
	SDLApplication* getGame() const { return myApp; };

	void addEventListener();
	void addObject(GameObject* obj);

private:
	SDLApplication* myApp;
};

