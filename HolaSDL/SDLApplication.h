#pragma once
#include "texture.h"
#include "FileNotFoundError.h"
#include "SDLError.h"


using namespace std;
const string textureRoot = "..\\images";

// Constantes
constexpr int NUM_TEXTURES = 16,
			  WIN_WIDTH = 800,
			  WIN_HEIGHT = 600;

enum TextureName {
	Stars,
	Spaceship,
	Bunkers,
	Aliens,
	UFOs,
	Numbers,
	MainMenu,
	Cargar,
	Codigo,
	Continuar,
	Over,
	Guardar,
	Ganado,
	Nueva,
	Salir,
	Volver
};

class SDLApplication
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
		img {"\\numbers.png", 1, 10},
		img {"\\mainMenu.png", 1, 1},
		img {"\\cargarPartida.png", 1, 1},
		img {"\\codigo.png", 1, 1},
		img {"\\continuar.png", 1, 1},
		img {"\\gameOver.png", 1, 1},
		img {"\\guardarPartida.png", 1, 1},
		img {"\\hasGanado.png", 1, 1},
		img {"\\nuevaPartida.png", 1, 1},
		img {"\\salir.png", 1, 1},
		img {"\\volverAlMenu.png", 1, 1}
	};

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture* auxTex[NUM_TEXTURES];

public:
	SDLApplication();
	Texture* getTexture(TextureName name) const;
};

