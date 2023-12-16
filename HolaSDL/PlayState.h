#pragma once
#include "GameState.h"
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
#include <fstream>
#include <iostream>
#include <ostream>
#include <cstdint>
#include <list>
#include "UFO.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "gameList.h"
#include "EndState.h"
#include <random>

using namespace std;

// Constantes
constexpr int PLAYER_VELOCITY = 4;

class Mothership;
class SDLApplication;

class PlayState :
	public GameState
{
private:
	static const std::string s_playID;

	bool 
		cannotMove = false,
		pause = false,
		saving = false;

	int myPoints;

	int ufoSpawnTime;

	mt19937_64 rdo;

	Vector2D<int> direction = Vector2D(1, 0);

	GameList<SceneObject, false> objectElems;
	//list<SceneObject*> objectToDelete;
	Mothership* mama;
	Cannon* player;

public:
	PlayState(SDLApplication* app);
	~PlayState();

	void Run();
	void FireLaser(Point2D<int> position, const char* color);
	int GetRandomRange(int min, int max);
	bool Damage(SDL_Rect rect, const char* c);
	void HasDied(GameList<SceneObject, false>::anchor it);
	void addPoints(int p);

	// Getters
	Vector2D<int> GetDirection() { return direction; }
	int GetAlienNums();

private:
	void Render() const override;
	void Update() override;
	void RenderPoints();
	void HandleEvent(const SDL_Event& event) override;
	void Menu();
	void LoadMaps(string map);
	void SpawnUFO();
	void Save(int k);

	bool onEnter() override { return true; }
	bool onExit() override { return true; }
	std::string getStateID() const override { return s_playID; }

};

