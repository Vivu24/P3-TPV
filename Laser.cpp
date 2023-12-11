#include "checkML.h"
#include "Laser.h"
#include "Game.h"

// Constructora
Laser::Laser(Game* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, const char* type)
	: SceneObject(game, texture, pos, w, h, l, f, c), myType(type) {};

// Render
void Laser::Render() const {
	// Si es del alien = roja
	if (myType == "r") {
		SDL_SetRenderDrawColor(myGame->GetRenderer(), 255, 0, 0, 255);
	}
	// Si es del player = azul
	else if (myType == "b") {
		SDL_SetRenderDrawColor(myGame->GetRenderer(), 0, 0, 255, 255);
	}

	SDL_RenderFillRect(myGame->GetRenderer(), &myRect);
}

// Moviento
void Laser::Move() {
	// Alien = abajo
	if (myType == "r") {
		myPosition = myPosition + myVelocity;
	}
	// Player = arriba
	else if (myType == "b") {
		myPosition = myPosition + myVelocity * -1;
	}
}

// Update
void Laser::Update() {
	// Rect del laser
	myRect = { myPosition.getX(), myPosition.getY(),
			   myWidth, myHeight };

	// Llamada al movimiento
	Move();

	// Eliminación de la bala con su colisión
	if(myGame->Damage(myRect, myType)) myGame->HasDied(myIterator);
}

// Hit
bool Laser::Hit(SDL_Rect rect, const char* c) {
	bool hasHit = false;

	// Devuelve true si ha tenido colisión
	if (SDL_HasIntersection(&rect, &myRect) && myType != c) {
		myGame->HasDied(myIterator);
		hasHit = true;
	}
	return hasHit;
}