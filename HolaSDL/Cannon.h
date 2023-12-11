#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include <list>
#include <ostream>
#include <iostream>

class Game;

class Cannon : public SceneObject
{
private:
	Vector2D<int> myDirection;
	int	cooldown;
	int currentCooldown;
	float reloadTime;
	bool input;

public:
	Cannon(Game* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, int cd);
	void Update() override;
	void HandleEvent(SDL_Event& event);
	void Move();
	bool Hit(SDL_Rect rect, const char* c) override;
	void Save(ostream& out) const override;
private:
	void Fire();
};

