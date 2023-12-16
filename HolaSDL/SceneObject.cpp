#include "SceneObject.h"
#include "SDLApplication.h"
#include "checkML.h"
#include "PlayState.h"

// Constructora
SceneObject::SceneObject(PlayState* game, GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c)
	: myGame(game), GameObject(state), myTexture(texture), myPosition(pos), myWidth(w), myHeight(h), myLifes(l), myFil(f), myCol(c) {}

// Render
void SceneObject::Render() const {
	// Creación del rect actual para su renderizado
	SDL_Rect rect = { myPosition.getX(), myPosition.getY(),
			   myWidth, myHeight };
	myTexture->renderFrame(rect, myFil, myCol);
}

// Hit
bool SceneObject::Hit(SDL_Rect rect, const char* c) {
	// Crea el rect
	SDL_Rect auxRect = { myPosition.getX(), myPosition.getY(),
			   myWidth, myHeight };
	bool hasHit = false;
	// Comprueba su colisión y si no tiene vidas lo elimina
	if (SDL_HasIntersection(&rect, &auxRect)) {
		--myLifes;
		if (myLifes <= 0) myGame->HasDied(myIterator);
		hasHit = true;
	}
	return hasHit;
}

// Guardado
void SceneObject::Save(ostream& out) const {
	out << myPosition.getX() << " " << myPosition.getY() << " ";
};

// Set del iterador del objeto
void SceneObject::setListAnchor(GameList<SceneObject, false>::anchor it) {
	myIterator = it;
}