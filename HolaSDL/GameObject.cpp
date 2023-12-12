#include "GameObject.h"
#include "PlayState.h"
#include "checkML.h"

GameObject::GameObject(SDLApplication* game) : myGame(game) {};

GameObject::~GameObject() { myGame = nullptr; }

void GameObject::Render() const {}

void GameObject::Update() {}

void GameObject::Save(ostream& out) const {}

