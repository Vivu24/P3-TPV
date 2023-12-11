#pragma once
#include "SceneObject.h"
#include <ostream>
#include <iostream>

class Game;

class UFO : public SceneObject
{
private:
	int currentState,
		points = 100,
		animationTimer = 10;

	enum State {
		OCULTO,
		VISIBLE,
		DESTRUIDO
	};

	int hideTime;
	Vector2D<int> myDirection = Vector2D(5, 0);

public:
	UFO(Game* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, int s, int cd);

	int GetState() { return currentState; }

	bool Hit(SDL_Rect rect, const char* c) override;
	void Save(ostream& out) const override;
private:
	void Move();
	void ChangeState(int lastState);
	void Update() override;
	void StateChecker();
	void ChangeDirection();
};

