#include "GameObject.h"
#include "Game.h"
#include "checkML.h"

GameObject::GameObject(Game* game) : myGame(game) {};

GameObject::~GameObject() { myGame = nullptr; }

void GameObject::Render() const {}

void GameObject::Update() {}

void GameObject::Save(ostream& out) const {}

