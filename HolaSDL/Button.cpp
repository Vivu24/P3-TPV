#include "Button.h"

Button::Button(Texture* tex) : myTexture(tex) {}

void Button::Connect(Callback newCb) {
	myCallbacks.push_back(newCb);
}