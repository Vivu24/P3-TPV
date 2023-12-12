#pragma once
#include <ostream>
#include <iostream>

using namespace std;

class PlayState;

class GameObject
{
protected:

	PlayState* myGame;

protected:

	GameObject();
	GameObject(PlayState* game);
	virtual ~GameObject();

public:
	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void Save(ostream& out) const = 0;
};

