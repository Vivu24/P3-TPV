#pragma once
#include <ostream>
#include <iostream>

using namespace std;

class Game;

class GameObject
{
protected:

	Game* myGame;

protected:

	GameObject();
	GameObject(Game* game);
	virtual ~GameObject();

	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void Save(ostream& out) const = 0;
};

