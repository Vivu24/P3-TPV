#pragma once
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include "GameList.h"
#include "GameObject.h"
#include <list>
#include "EventHandler.h"
#include "SDLApplication.h"

class SDLApplication;

class GameState
{
protected:
	GameList<GameObject, true> myList;
	list<EventHandler*> myEvents;
	// Puntero al juego
	SDLApplication* myApp;

public: 
	GameState(SDLApplication* app) : myApp(app) {}
	GameState(const GameState& state) : myApp(state.myApp) {
		myList = state.myList;
		myEvents = state.myEvents;
	};

	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void HandleEvent(const SDL_Event&) = 0;
	virtual void Save(ostream&) const = 0;
	virtual void HasDied(GameList<GameObject, true>::anchor) = 0;
	SDLApplication* getGame() const { return myApp; };

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;


	void addEventListener();
	void addObject(GameObject* obj);

private:
	SDLApplication* myApp;
};

