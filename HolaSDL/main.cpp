#include "checkML.h"

#include "SDL.h"
#include "texture.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char* argv[])
{	
	try {
		Game cacaolat = Game();
		cacaolat.Run();
	}
	catch (InvadersError& e) {
		cout << e.what();
	}
	
	return 0;
}
