#include "checkML.h"
#include "Cannon.h"
#include "Game.h"


// Constructora
Cannon::Cannon(Game* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, int cd) :
	SceneObject(game, texture, pos, w, h, l, f, c), cooldown(cd){
	currentCooldown = cooldown;
}

// Disparo
void Cannon::Fire() {
	myGame->FireLaser(myPosition, "b");
	input = false;
}

// Eventos
void Cannon::HandleEvent(SDL_Event &event) {
	// Disparo
	if (event.key.keysym.sym == SDLK_SPACE) {
		if (currentCooldown <= 0)  {
			Fire();
			currentCooldown = cooldown; // Tiempo de recarga
		};
	}
	// Movimiento a la derecha
	else if (event.key.keysym.sym == SDLK_RIGHT) {
		myDirection = Vector2D(1, 0);
	}
	// Movimiento a la izquierda
	else if (event.key.keysym.sym == SDLK_LEFT) {
		myDirection = Vector2D(-1, 0);
	}

	// Hay input
	input = true;
}

// Update del cannon
void Cannon::Update() {
	Move();
	--currentCooldown;
}

// Movimiento del canon
void Cannon::Move() {
	// Evitar salirnos del limite del mapa
	if (myPosition.getX() < 0) myPosition = Point2D<int>(0, myPosition.getY());
	if (myPosition.getX() + myTexture->getFrameWidth() > WIN_WIDTH) myPosition = Point2D<int>(WIN_WIDTH - myTexture->getFrameWidth(), myPosition.getY());

	// Movimiento
	if (input) {
		myPosition = myPosition + myDirection * PLAYER_VELOCITY;
		myDirection = Vector2D(0, 0); // Ponemos a 0 la direcci�n
		input = false;
	}
}

// Colisi�n del cannon
bool Cannon::Hit(SDL_Rect rect, const char* c) {
	// Creaci�n del rect
	SDL_Rect auxRect = { myPosition.getX(), myPosition.getY(),
		   myWidth, myHeight };

	bool hasHit = false;

	// Comprobaci�n de la colisi�n con la bala
	if (SDL_HasIntersection(&rect, &auxRect) && c == "r") {
		--myLifes;
		if (myLifes <= 0) {
			myGame->HasDied(myIterator);
			++myIterator;
		}
		hasHit = true;
	}
	return hasHit;
}

// Guardado
void Cannon::Save(ostream& out) const {
	out << 0 << " ";
	SceneObject::Save(out);
	out << myLifes << " " << cooldown << "\n";
}