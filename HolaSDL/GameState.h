#pragma once
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include "gameList.h"
#include "GameObject.h"
#include <list>
#include "EventHandler.h"
class SDLApplication;

class GameState
{
protected:
	GameList<GameObject, true> myList;
	list<EventHandler*> myEvents;
	bool pop = false;

public: 
	GameState(SDLApplication* app) : myApp(app) {}
	GameState(const GameState& state) : myApp(state.myApp) {
		myList = state.myList;
		myEvents = state.myEvents;
	};

	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void HandleEvent(const SDL_Event&) = 0;
	void Save(ostream&) const;
	void HasDied(GameList<GameObject, true>::anchor it);
	SDLApplication* getGame() const { return myApp; };

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;


	void addEventListener(EventHandler* event);
	void addObject(GameObject* obj);

	void SetPop(bool p) { pop = p; }
private:
	SDLApplication* myApp;
};

