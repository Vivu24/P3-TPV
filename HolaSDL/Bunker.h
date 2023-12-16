#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include <list>
#include <ostream>
#include <iostream>

class Bunker : public SceneObject
{
public:
	Bunker(PlayState* game, GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c);
	void Render() const override;
	void Update() override;
	void Save(ostream& out) const override;
};

