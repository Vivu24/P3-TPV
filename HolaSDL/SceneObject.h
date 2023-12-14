#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include "texture.h"
#include <list>
#include "gameList.h"

class PlayState;

class SceneObject : public GameObject
{
protected:
	GameList<SceneObject, false>::anchor myIterator;
	PlayState* myGame;
	Point2D<int> myPosition;
	int myWidth,
		myHeight,
		myLifes,
		myFil,
		myCol;
	SDL_Rect myRect;
	Texture* myTexture;

public:
	SceneObject();
	SceneObject(GameState* state, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c);

	virtual bool Hit(SDL_Rect rect, const char* c);
	void Render() const override;
	void Update() override = 0;
	void Save(ostream& out) const override;

	void setListAnchor(GameList<SceneObject, false>::anchor it);
};

