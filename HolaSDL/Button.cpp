#include "Button.h"

Button::Button(GameState* state, Texture* tex, Point2D<int> pos) : myTexture(tex), GameObject(state), EventHandler(), myPosition(pos) {}

void Button::Connect(Callback newCb) {
	myCallbacks.push_back(newCb);
}

void Button::Render() const {
	SDL_Rect myRect = { myPosition.getX(), myPosition.getY(), myTexture->getFrameWidth(), myTexture->getFrameHeight()};
	myTexture->renderFrame(myRect, 0, 0);
}

void Button::HandleEvent(const SDL_Event& event) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX >= myPosition.getX() && mouseX < myPosition.getX() + myTexture->getFrameWidth() &&
		mouseY >= myPosition.getY() && mouseY < myPosition.getY() + myTexture->getFrameHeight()) {
		for (Callback c : myCallbacks) {
			c();
		}
	}
}