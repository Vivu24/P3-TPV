#include "EndState.h"
#include "SDLApplication.h"
#include "texture.h"
#include "Vector2D.h"

const std::string EndState::s_menuID = "END";

EndState::EndState(SDLApplication* app) : GameState(app) {
	CreateButtons();
}

void EndState::Render() const {
	SDL_SetRenderDrawColor(getGame()->GetRenderer(), 0, 0, 0, 255);
	//SDL_SetTextureColorMod(getGame()->getTexture(TextureName::Over), );
	SDL_Rect rect = { WIN_WIDTH / 2 - getGame()->getTexture(TextureName::Over)->getFrameWidth() / 2, 150, getGame()->getTexture(TextureName::Over)->getFrameWidth(), getGame()->getTexture(TextureName::Over)->getFrameHeight()};
	getGame()->getTexture(TextureName::Over)->renderFrame(rect, 0, 0);
	for (GameObject& obj : myList) {
		obj.Render();
	}
}

void EndState::Update() {
	if (pop) getGame()->ReplaceState(new MainMenuState(getGame()));
}

void EndState::HandleEvent(const SDL_Event& e) {
	for (EventHandler* b : myEvents) {
		b->HandleEvent(e);
	}
}

bool EndState::onEnter()
{
	return true;
}

bool EndState::onExit()
{
	return true;
}

void EndState::CreateButtons() {
	SDLApplication* myApp = getGame();
	Button* obj = new Button(this, myApp->getTexture(TextureName::Volver), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Volver)->getFrameWidth() / 2, WIN_HEIGHT / 2));
	obj->Connect([this]() {
		pop = true;
	});
	addObject(obj);
	addEventListener(obj);
	obj = new Button(this, myApp->getTexture(TextureName::Salir), Point2D<int>(WIN_WIDTH / 2 - myApp->getTexture(TextureName::Salir)->getFrameWidth() / 2, 450));
	addObject(obj);
	addEventListener(obj);
}
