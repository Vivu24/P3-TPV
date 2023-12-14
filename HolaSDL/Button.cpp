#include "Button.h"

Button::Button(GameState* state, Texture* tex) : myTexture(tex), GameObject(state), EventHandler() {}

void Button::Connect(Callback newCb) {
	myCallbacks.push_back(newCb);
}

void Button::Render() const {
	SDL_Rect myRect = { 0, 0, myTexture->getFrameWidth(), myTexture->getFrameHeight() };
	myTexture->renderFrame(myRect, 0, 0);
}