#include "GameObject.h"
#include "GameState.h"
#include "checkML.h"

GameObject::GameObject(GameState* state) : myState(state) {};

GameObject::~GameObject() { myState = nullptr; }

void GameObject::Render() const {}

void GameObject::Update() {}

void GameObject::Save(ostream& out) const {}

// Set del iterador del objeto
void GameObject::setListAnchor(GameList<GameObject, true>::anchor it) {
	myAnchor = it;
}