#pragma once
#include "Alien.h"
#include "Mothership.h"

class ShooterAlien : public Alien
{
public:
	ShooterAlien(PlayState* game, GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, Mothership* mama, int cd);
	void Save(ostream& out) const override;
private:
	int cooldown;
	int currentCooldown;

	void Fire();

	void Update() override;
};