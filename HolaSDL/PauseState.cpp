#include "PauseState.h"
#include "SDLApplication.h"
#include "texture.h"
#include "Vector2D.h"
#include "PlayState.h"

PauseState::PauseState(SDLApplication* app) : GameState(app) {
	CreateButtons();
}
const std::string MainMenuState::s_menuID = "PAUSE";

void PauseState::Render() const {
	SDLApplication* myApp = getGame();
	myApp->getTexture(TextureName::MainMenu)->render();

	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void PauseState::Update() {
	if (pop) getGame()->ReplaceState(new PlayState(getGame()));
}

void PauseState::HandleEvent(const SDL_Event& e) {
	for (EventHandler* b : myEvents) {
		b->HandleEvent(e);
	}
}

bool PauseState::onEnter() { return true; }

bool PauseState::onExit() { return true; }

void PauseState::CreateButtons() {
	SDLApplication* myApp = getGame();
	Button* obj = new Button(this, myApp->getTexture(TextureName::Continuar), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Continuar)->getFrameWidth() / 2, 200));
	//obj->Connect([this]() {})
	addObject(obj);
	addEventListener(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Guardar), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Guardar)->getFrameWidth() / 2, 150));
	obj->Connect([this]() {
		pop = true;
		});
	addObject(obj);
	addEventListener(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Cargar), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Cargar)->getFrameWidth() / 2, 150));
	obj->Connect([this]() {
		pop = true;
		});
	addObject(obj);
	addEventListener(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Salir), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Salir)->getFrameWidth() / 2, 250));
	addObject(obj);
	addEventListener(obj);
}