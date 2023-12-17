#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"

using namespace std;

class Reward : public SceneObject
{
private:
	Vector2D<int> myDirection = Vector2D(-1, 0);
public:
	Reward(PlayState* game, GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c);
	bool Hit(SDL_Rect rect, const char* c) override;
	void Save(ostream& out) const override;

protected:
	void Move();
	void Update() override;
};

