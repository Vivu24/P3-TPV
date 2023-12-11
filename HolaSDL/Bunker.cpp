#include "checkML.h"
#include "Bunker.h"
#include <SDL_image.h>

using namespace std;

// Constructora
Bunker::Bunker(Game* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c) :
	SceneObject(game, texture, pos, w, h, l, f, c) {};

// Render
void Bunker::Render() const{
	SDL_Rect auxRect = { myPosition.getX(), myPosition.getY(),
						myWidth, myHeight };
	myTexture->renderFrame(auxRect, myFil, 4 - myLifes);
}

void Bunker::Update() {}

void Bunker::Save(ostream& out) const {
	out << 4 << " ";
	SceneObject::Save(out);
	out << myLifes << "\n";
}