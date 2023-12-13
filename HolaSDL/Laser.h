#pragma once
#include "Vector2D.h";
#include "SceneObject.h"
#include "SDL.h"
#include <ostream>
#include <iostream>

class Laser : public SceneObject
{
private:
	Vector2D<int> myVelocity = Vector2D(0, 5);
	const char* myType;

public:
	Laser(GameState* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, const char* type);

	bool Hit(SDL_Rect rect, const char* c) override;

	// Getters
	const char* GetBulletType() { return myType; }
private:
	void Render() const override;
	void Move(); 
	void Update() override;
};


