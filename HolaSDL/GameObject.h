#pragma once
#include <ostream>
#include <iostream>

using namespace std;

class SDLApplication;

class GameObject
{
protected:

	SDLApplication* myGame;

protected:

	GameObject();
	GameObject(SDLApplication* game);
	virtual ~GameObject();

	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void Save(ostream& out) const = 0;
};

