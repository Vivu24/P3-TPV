#pragma once
#include <ostream>
#include <iostream>
#include "gameList.h"

using namespace std;

class GameState;

class GameObject
{
protected:

	GameState* myState;

protected:
	GameList<GameObject, true>::anchor myAnchor;

public:

	GameObject();
	GameObject(GameState* state);
	virtual ~GameObject();
	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void Save(ostream& out) const = 0;

	void setListAnchor(GameList<GameObject, true>::anchor it);

	GameList<GameObject, true>::anchor getIterator() { return myAnchor; };
};

