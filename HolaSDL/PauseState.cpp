#include "PauseState.h"
#include "SDLApplication.h"

const std::string PauseState::s_menuID = "PAUSE";

void PauseState::Render() const {
	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void PauseState::Update() {}

void PauseState::HandleEvent(const SDL_Event& e) {}

bool PauseState::onEnter() { return true; }

bool PauseState::onExit() { return true; }

void PauseState::CreateButtons() {
	SDLApplication* myApp = getGame();
	GameObject* obj = new Button(this, myApp->getTexture(TextureName::Continuar));
	addObject(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Cargar));
	addObject(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Guardar));
	addObject(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Salir));
	addObject(obj);
}