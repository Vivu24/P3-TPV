#include "MainMenuState.h"
#include "SDLApplication.h"
void MainMenuState::Render() const {
	SDLApplication* myApp = getGame();
	myApp->getTexture(TextureName::MainMenu)->render();

	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void MainMenuState::CreateButtons() {
	SDLApplication* myApp = getGame();
	GameObject* obj = new Button(myApp->getTexture(TextureName::Cargar));
	addObject(obj);
}