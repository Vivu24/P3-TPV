#include "checkML.h"
#include "Alien.h"
#include "Game.h"

// Constructora
Alien::Alien(PlayState* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, Mothership* mama) :
	SceneObject(game, texture, pos, w, h, l, f, c), myMama(mama) {
	if (f == 0) points = 30;
	else if (f == 1) points = 20;
	else if (f == 2) points = 10;

	iniY = myPosition.getY();
};

// Movimiento
void Alien::Move() {
	myPosition = myMama->getDirection() + myPosition;
	myPosition = Point2D<int>(myPosition.getX(), iniY + myMama->getLevel());
}

bool Alien::Hit(SDL_Rect rect, const char* c) {
	SDL_Rect auxRect = { myPosition.getX(), myPosition.getY(),
		   myWidth, myHeight };
	bool hasHit = false;
	if (SDL_HasIntersection(&rect, &auxRect) && c == "b") {
		--myLifes;
		if (myLifes <= 0) {
			myGame->addPoints(points);
			myGame->HasDied(myIterator);
			myMama->alienDied();
		}
		hasHit = true;
	}
	return hasHit;
}

void Alien::Update() {
	Move();
	if (myPosition.getY() + myTexture->getFrameHeight() >= 400) myMama->alienLanded();
	if (myPosition.getX() <= 0 || myPosition.getX() + myTexture->getFrameWidth() >= WIN_WIDTH) myMama->cannotMove();
}

void Alien::Save(ostream& out) const{
	out << 1 << " ";
	SceneObject::Save(out);
	out << myFil << "\n";
}
