#include "MainMenuState.h"
#include "SDLApplication.h"
#include "texture.h"
#include "Vector2D.h"
#include "PlayState.h"

MainMenuState::MainMenuState(SDLApplication* app) : GameState(app) {
	CreateButtons();
}
const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::Render() const {
	SDLApplication* myApp = getGame();
	myApp->getTexture(TextureName::MainMenu)->render();

	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void MainMenuState::Update() {
	if(pop) getGame()->ReplaceState(new PlayState(getGame()));
} 

void MainMenuState::HandleEvent(const SDL_Event& e) {
	for (EventHandler* b : myEvents) {
		b->HandleEvent(e);
	}
}

bool MainMenuState::onEnter() { return true; }

bool MainMenuState::onExit() { return true; }

void MainMenuState::CreateButtons() {
	SDLApplication* myApp = getGame();
	Button* obj = new Button(this, myApp->getTexture(TextureName::Cargar), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Cargar)->getFrameWidth() / 2, 200));
	//obj->Connect([this]() {})
	addObject(obj);
	addEventListener(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Nueva), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Nueva)->getFrameWidth() / 2, 150));
	obj->Connect([this]() {
		pop = true;
	});
	addObject(obj);
	addEventListener(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Salir), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Salir)->getFrameWidth() / 2, 250));
	addObject(obj);
	addEventListener(obj);
}