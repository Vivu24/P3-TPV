#include "checkML.h"
#include "Reward.h"
#include "SDLApplication.h"

Reward(PlayState* game, GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c) 
SceneObject(game, state, texture, pos, w, h, l, f, c) {}

// Movimiento
void Reward::Move() {
	myPosition= myPosition + myDirection;
}
