#include "Mothership.h"
#include "Game.h"
#include "checkML.h"

// Constructora
Mothership::Mothership(Game* game) : GameObject(game) {};

// Update
void Mothership::Update() {
	if (cantMove) {
		level += levelDescension;
		ChangeDirection();
	}

	if (alienNum == 0) myGame->SetExit();
}

void Mothership::ChangeDirection() {
	/*if (currentState == RIGHT) currentState == LEFT;
	else if (currentState == LEFT) currentState == RIGHT;*/
	myDirection = myDirection * -1;
	cantMove = false;
}

// GetDirection
Vector2D<int> Mothership::getDirection() const{
	return myDirection;
}

// CannotMove
void Mothership::cannotMove() {
	cantMove = true;
}

// GetAlienCount
int Mothership::getAlienCount() const{
	return myGame->GetAlienNums();
}

// Pregunta si han llegado abajo
void Mothership::alienLanded() {
	haveLanded();
}

// Cuando llegan abajo hace la llamada necesaria para finalizar el juego
void Mothership::haveLanded() {
	myGame->SetExit();
}

// Elimina un alien de la cuenta total
void Mothership::alienDied() {
	--alienNum;
}

void Mothership::Render() const {}

// Añade un alien a la cuenta total
void Mothership::addAlien() {
	++alienNum;
}

// Getter de level
int Mothership::getLevel() {
	return level;
}

// Guardado
void Mothership::Save(ostream& out) const {
	out << 3 << " ";
	out << waitTime << "\n";
}

// Actualiza la Mothership al cargar una partida
void Mothership::SetMothership(int l, int cd) {
	level = l;
	waitTime = cd;
}