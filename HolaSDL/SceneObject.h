#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include "texture.h"
#include <list>

class SceneObject : public GameObject
{
protected:
	Point2D<int> myPosition;
	int myWidth,
		myHeight,
		myLifes,
		myFil,
		myCol;
	SDL_Rect myRect;
	Texture* myTexture;
	std::list<SceneObject*>::iterator myIterator;

public:
	SceneObject();
	SceneObject(PlayState* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c);

	virtual bool Hit(SDL_Rect rect, const char* c);
	void setListIterator(std::list<SceneObject*>::iterator it);
	void Render() const override;
	void Update() override = 0;
	void Save(ostream& out) const override;

	std::list<SceneObject*>::iterator getIterator() { return myIterator; };
};

