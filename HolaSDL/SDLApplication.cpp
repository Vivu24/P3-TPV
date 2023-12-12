#include "SDLApplication.h"

SDLApplication::SDLApplication() {
	// Inicializacion de SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw SDLError("Error de SDL: "s + SDL_GetError());
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	// Carga de texturas en el array
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		try {
			auxTex[i] =
				new Texture(renderer, (textureRoot + imgs[i].name).c_str(),
					imgs[i].horizontalFrames, imgs[i].verticalFrames);
		}
		catch (...) {
			throw FileNotFoundError("Error al cargar la textura: "s + imgs[i].name);
		}
	}
}

Texture* SDLApplication::getTexture(TextureName name) const {
	return auxTex[name];
}