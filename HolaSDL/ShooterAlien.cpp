#include "ShooterAlien.h"
#include "SDLApplication.h"
#include "checkML.h"

// Constructora
ShooterAlien::ShooterAlien(GameState* game, Texture* texture, Vector2D<int> pos, int w, int h, int l, int f, int c, Mothership* mama, int cd) :
	Alien(game, texture, pos, w, h, l, f, c, mama), cooldown(cd) {
	currentCooldown = cooldown;
}

// Disparo
void ShooterAlien::Fire() {
	myGame->FireLaser(myPosition, "r");
	currentCooldown = cooldown; // Recarga
}

// Update
void ShooterAlien::Update() {
	// Update base del alien
	Alien::Update();

	// + Logica de disparo con aleatorios
	int aux = myGame->GetRandomRange(1, 2500);
	if (aux == 1 && currentCooldown <= 0) Fire();
	--currentCooldown; // Disminuye la recarga
}

// Guardado
void ShooterAlien::Save(ostream& out) const {
	out << 2 << " ";
	SceneObject::Save(out);
	out << 0 << " " << cooldown << "\n";
}
