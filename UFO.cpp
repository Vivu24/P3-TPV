#include "UFO.h"
#include "Game.h"
#include "checkML.h"

// Constructora
UFO::UFO(Game* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, int s, int cd)
	: SceneObject(game, texture, pos, w, h, l, f, c), currentState(s), hideTime(cd) {};

// Movimiento
void UFO::Move() {
	myPosition = myPosition - myDirection;
}

// Comprueba el estado del UFO y lo actualiza según sea necesario
void UFO::StateChecker() {
	if (currentState == OCULTO && hideTime <= 0) {
		ChangeState(VISIBLE);
		hideTime = myGame->GetRandomRange(100, 500);
	}
	else if (currentState == VISIBLE && (myPosition.getX() >= WIN_WIDTH || (myPosition.getX() + myWidth) <= 0)) {
		ChangeState(OCULTO);
		ChangeDirection();
	}
	else if (myLifes <= 0) {
		ChangeState(DESTRUIDO);
	}
}

// Cambio de estado
void UFO::ChangeState(int state) {
	currentState = state;
}

// Update
void UFO::Update() {
	StateChecker();
	if (currentState == OCULTO) --hideTime;
	else if (currentState == VISIBLE) Move();
	else if (currentState == DESTRUIDO) ++myCol;
}

// Cambio de dirección del UFO
void UFO::ChangeDirection() {
	myDirection = myDirection * -1;
}

// Hit
bool UFO::Hit(SDL_Rect rect, const char* c) {
	// Creación del rect para comprobar si ha colisionado y así actuar consecuentemente
	SDL_Rect auxRect = { myPosition.getX(), myPosition.getY(),
			   myWidth, myHeight };
	bool hasHit = false;
	if (SDL_HasIntersection(&rect, &auxRect)) {
		myGame->addPoints(points);
		--myLifes;
		hasHit = true;
	}
	return hasHit;
}

// Guardado
void UFO::Save(ostream& out) const {
	out << 5 << " ";
	SceneObject::Save(out);
	out << currentState << " " << hideTime << "\n";
}