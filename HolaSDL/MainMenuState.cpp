#include "MainMenuState.h"
#include "SDLApplication.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::Render() const {
	PlayState* myApp = getGame();
	myApp->getTexture(TextureName::MainMenu)->render();

	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void MainMenuState::Update() {}

void MainMenuState::HandleEvent(const SDL_Event&) {}

void MainMenuState::Save(ostream&) const {}

void MainMenuState::HasDied(GameList<GameObject, true>::anchor) {}

bool MainMenuState::onEnter() {}

bool MainMenuState::onExit() {}

void MainMenuState::CreateButtons() {
	PlayState* myApp = getGame();
	GameObject* obj = new Button(myApp->getTexture(TextureName::Cargar));
	addObject(obj);
	obj = new Button(myApp->getTexture(TextureName::Nueva));
	addObject(obj);
	obj = new Button(myApp->getTexture(TextureName::Salir));
	addObject(obj);
}