#pragma once
#include <SDL.h> 
#include <vector>
#include "Laser.h"
#include "Alien.h"
#include "ShooterAlien.h"
#include "Bunker.h"
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <ostream>
#include <cstdint>
#include <list>
#include "UFO.h"
#include "Mothership.h"


using namespace std;
const string textureRoot = "..\\images";

// Constantes
constexpr int  WIN_WIDTH = 800,
			   WIN_HEIGHT = 600,
			   NUM_TEXTURES = 6,
			   PLAYER_VELOCITY = 4,
			   FRAME_RATE = 30;


class Game
{
private:
	// Struct para cada imagen del juego
	struct img {
		string name;
		int horizontalFrames;
		int verticalFrames;
	};

	// Array de imagenes
	const img imgs[NUM_TEXTURES]{
		img {"\\stars.png", 1, 1},
		img {"\\spaceship.png", 1, 1},
		img {"\\bunker.png", 1, 4},
		img {"\\aliens.png", 3, 2},
		img {"\\ufo.png", 1, 2},
		img {"\\numbers.png", 1, 10}
	};

	bool exit = false,
		cannotMove = false,
		pause = false,
		saving = false;

	int myPoints;

	int ufoSpawnTime;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	mt19937_64 rdo = mt19937_64(time(nullptr));
	
	Vector2D<int> direction = Vector2D(1, 0);

	list<SceneObject*> objectElems;
	list<SceneObject*> objectToDelete;
	Mothership* mama;
	Cannon* player;

	Texture* textures[NUM_TEXTURES];

	enum TextureName {
		Stars,
		Spaceship,
		Bunkers,
		Aliens,
		UFOs,
		Numbers
	};

public:
	Game();
	~Game();

	void Run();
	void FireLaser(Point2D<int> position, const char* color);
	int GetRandomRange(int min, int max);
	bool Damage(SDL_Rect rect, const char* c);
	void HasDied(const list<SceneObject*>::iterator& it);
	void addPoints(int p);

	// Getters
	SDL_Renderer* GetRenderer() { return renderer; }
	Vector2D<int> GetDirection() { return direction; }
	int GetAlienNums();

	// Setters
	void SetExit() { exit = true; }
private:
	void Render();
	void Update();
	void RenderPoints();
	void HandleEvents();
	void Menu();
	void LoadMaps(string map);
	void SpawnUFO();
	void Save(int k);
};

