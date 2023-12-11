#pragma once
#include "Vector2D.h"
#include "GameObject.h"
#include <ostream>
#include <iostream>

using namespace std;

class Game;

class Mothership : public GameObject
{
private:
	const int levelDescension = 20;
	bool cantMove = false;
	int level = 0,
		waitTime = 100,
		alienNum = 0;
		/*currentState = RIGHT;*/

	/*enum state {
		LEFT = -1,
		RIGHT = 1
	};*/

	Vector2D<int> myDirection = Vector2D<int>(1, 0);

	int getAlienCount() const;
	void haveLanded();
	void ChangeDirection();
	void Render() const override;

public:
	Mothership(Game* game);

	void alienDied();
	void alienLanded();
	Vector2D<int> getDirection() const;
	void cannotMove();
	void Update() override;
	void addAlien();
	int getLevel();
	bool canIMove();
	void Save(ostream& out) const override;
	void SetMothership(int l, int cd);
};

