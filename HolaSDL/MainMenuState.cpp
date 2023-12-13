#include "MainMenuState.h"
#include "SDLApplication.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::Render() const {
	SDLApplication* myApp = getGame();
	myApp->getTexture(TextureName::MainMenu)->render();

	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void MainMenuState::Update() {}

void MainMenuState::HandleEvent(const SDL_Event& e) {}

bool MainMenuState::onEnter() { return; }

bool MainMenuState::onExit() { return; }

void MainMenuState::CreateButtons() {
	SDLApplication* myApp = getGame();
	GameObject* obj = new Button(myApp->getTexture(TextureName::Cargar));
	addObject(obj);
	obj = new Button(myApp->getTexture(TextureName::Nueva));
	addObject(obj);
	obj = new Button(myApp->getTexture(TextureName::Salir));
	addObject(obj);
}