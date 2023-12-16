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
			textures[i] =
				new Texture(renderer, (textureRoot + imgs[i].name).c_str(),
					imgs[i].horizontalFrames, imgs[i].verticalFrames);
		}
		catch (...) {
			throw FileNotFoundError("Error al cargar la textura: "s + imgs[i].name);
		}
	}

	machine = new GameStateMachine();
	machine->PushState(new MainMenuState(this));

	//for(;;) textures[0]->render();
}

void SDLApplication::Run() {
	uint32_t startTime,
		frameTime;
	while (machine->currentState() != nullptr) {
		startTime = SDL_GetTicks();
		Update();
		Render();
		HandleEvents();

		/*frameTime = SDL_GetTicks() - startTime;

		if (frameTime <= FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);*/
	}
}

void SDLApplication::Update() {
	machine->Update();
}

void SDLApplication::Render() const {
	SDL_RenderClear(renderer);
	machine->Render();
	SDL_RenderPresent(renderer);
}

Texture* SDLApplication::getTexture(TextureName name) const {
	return textures[name];
}

void SDLApplication::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		machine->currentState()->HandleEvent(event);
	}
}

void SDLApplication::PushState(GameState* state) {
	machine->PushState(state);
}

void SDLApplication::ReplaceState(GameState* state) {
	machine->ReplaceState(state);
}

void SDLApplication::PopState() {
	machine->PopState();
}