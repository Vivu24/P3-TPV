#include "checkML.h"

#include "SDL.h"
#include "texture.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include <iostream>
#include "MainMenuState.h"
#include "SDLApplication.h"

using namespace std;


int main(int argc, char* argv[])
{	
	/*try {
		PlayState cacaolat = PlayState();
		cacaolat.Run();
	}
	catch (InvadersError& e) {
		cout << e.what();
	}
	
	return 0;*/

	SDLApplication cacaolat2 = SDLApplication();
	cacaolat2.Run();

	return 0;
}
