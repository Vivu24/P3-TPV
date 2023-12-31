#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include <list>
#include <ostream>
#include <iostream>

using namespace std;

class Mothership;

class Alien : public SceneObject
{
protected:
	Mothership* myMama;
	int iniY,
		points;

public:
	Alien(PlayState* game, GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, Mothership* mama);
	bool Hit(SDL_Rect rect, const char* c) override;
	void Save(ostream& out) const override;

protected:
	void Move();
	void Update() override;
};

