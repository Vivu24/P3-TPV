#include "checkML.h"
#include "Laser.h"
#include "Game.h"

// Constructora
Laser::Laser(SDLApplication* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, const char* type)
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

	// Eliminaci�n de la bala con su colisi�n
	if(myGame->Damage(myRect, myType) || myLifes <= 0) myGame->HasDied(myIterator);
}

// Hit
bool Laser::Hit(SDL_Rect rect, const char* c) {
	bool hasHit = false;

	// Devuelve true si ha tenido colisi�n
	if (SDL_HasIntersection(&rect, &myRect) && myType != c) {
		--myLifes;
		hasHit = true;
	}
	return hasHit;
}