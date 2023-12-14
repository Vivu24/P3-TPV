#include "MainMenuState.h"
#include "SDLApplication.h"
#include "texture.h"

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

bool MainMenuState::onEnter() { return true; }

bool MainMenuState::onExit() { return true; }

void MainMenuState::CreateButtons() {
	SDLApplication* myApp = getGame();
	GameObject* obj = new Button(this, myApp->getTexture(TextureName::Cargar));
	addObject(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Nueva));
	addObject(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Salir));
	addObject(obj);
}