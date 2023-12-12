#include "checkML.h"
#include "PlayState.h"

// Constructora
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

	mama = new Mothership(this);

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



	Menu();
}

// Destructora
SDLApplication::~SDLApplication() {
	for (auto i : textures) delete i;
	for (auto i : objectElems) delete i;
	delete mama;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Menu de incio
void SDLApplication::Menu() {
	int res;
	cout << "Pulse los siguientes n�meros para cargar los mapas \n";
	cout << "1 - Original / 2 - Trinchera / 3 - Lluvia \n";
	cin >> res;

	string auxFileName;

	// Eleccion de mapa de base
	switch (res) {
	case (1):
		auxFileName = "original.txt";
		break;
	case (2):
		auxFileName = "trinchera.txt";
		break;
	case (3):
		auxFileName = "lluvia.txt";
		break;
	default:
		break;
	}

	// Carga del mapa seleccionado
	LoadMaps(auxFileName);
}

// Ejecucion del juego
void SDLApplication::Run() {
	uint32_t startTime,
		frameTime;
	// Mientras el jugador este vivo o no hayan muerto todos los aliens
	while (!exit) {
		startTime = SDL_GetTicks();
		SDL_RenderClear(renderer);
		Update();
		Render();
		HandleEvents();
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime <= FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
	}

	cout << "A POR EL SPACE INVADERS 3.0";
};

// Render general
void SDLApplication::Render() {
	textures[Stars]->render();
	// Renderizado de todos los objetos de escena
	for (SceneObject& obj : objectElems) {
		obj.Render();
	}
	// Renderizado de la puntuaci�n
	RenderPoints();

	SDL_RenderPresent(renderer);
}

// Render de los puntos
void SDLApplication::RenderPoints() {
	SDL_Rect scoreRect = { 0, 550, 50, 50 };
	textures[Numbers]->renderFrame(scoreRect, 0, (myPoints / 1000) % 1000);
	scoreRect = { 50, 550, 50, 50 };
	textures[Numbers]->renderFrame(scoreRect, 0, (myPoints / 100) % 100);
	scoreRect = { 100, 550, 50, 50 };
	textures[Numbers]->renderFrame(scoreRect, 0, (myPoints / 10) % 10);
	scoreRect = { 150, 550, 50, 50 };
	textures[Numbers]->renderFrame(scoreRect, 0, 0);
}

// Update general
void SDLApplication::Update() {
	// Update de los scenesObjects
	for (SceneObject& obj : objectElems) {
		obj.Update();
	}
	// Lista auxiliar para eliminar los objetos
	for (auto i : objectToDelete) {
		objectElems.erase(i->getIterator());
		delete i;
	}

	if (objectToDelete.size() > 0) {
		objectToDelete.clear();
	}

	// Actualizaci�n del update de la mothership
	mama->Update();

}

// Manejo de eventos
void SDLApplication::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) && !exit)
	{
		if (pause)
		{
			if (event.type == SDL_KEYDOWN)
			{
				// Cuando es un n�mero v�lido para guardar archivo
				if (event.key.keysym.sym > 47 && event.key.keysym.sym < 58)
				{
					if (saving)
					{
						// Guardamos en el n�mero determinado
						Save(event.key.keysym.sym - 48);
					}
					else
					{
						// Borramos lo que haya en la escena para crear la nueva cargando el mapa que deseemos
						delete player;
						objectElems.clear();
						LoadMaps("saved" + to_string(event.key.keysym.sym - 48) + ".txt");
						pause = false;
					}
				}
				else
				{
					pause = false;
					saving = false;
				}
			}
		}
		else
		{
			player->HandleEvent(event);
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_s)
				{
					system("cls");
					cout << "N�mero de archivo: ";
					pause = true;
					saving = true;
				}
				else if (event.key.keysym.sym == SDLK_l)
				{
					system("cls");
					cout << "N�mero de archivo: ";
					pause = true;
					saving = false;
				}
			}
		}
		if (event.type == SDL_QUIT) {
			exit = true;
		}
	}
}

// Disparar
void SDLApplication::FireLaser(Point2D<int> position, const char* color) {
	// Creamos el laser y se a�ade al vector
	Laser* l = new Laser(this, nullptr, position, 10, 20, 1, 0, 0, color);
	objectElems.push_back(l);
	l->setListIterator(prev(objectElems.end()));
}

void SDLApplication::SpawnUFO() {
	UFO* u = new UFO(this, textures[UFOs], Vector2D<int>(800, 10), textures[UFOs]->getFrameWidth(), textures[UFOs]->getFrameHeight(), 1, 0, 0, 0, 200);
	objectElems.push_back(u);
	u->setListIterator(prev(objectElems.end()));
}

// Generador de aleatorios
int SDLApplication::GetRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(rdo);
}

// Colisiones
bool SDLApplication::Damage(SDL_Rect rect, const char* c) {
	for (list<SceneObject*>::iterator it = objectElems.begin(); it != objectElems.end(); ++it) {
		if ((*it)->Hit(rect, c)) return true;
	}
	return false;
}

// Carga de mapas
void SDLApplication::LoadMaps(string map) {
	// Flujo de entrada
	ifstream entrada(map);

	if (!entrada.is_open()) {
		throw FileNotFoundError("Error archivo no encontrado: "s + map);
	}

	if (entrada.peek() == ifstream::traits_type::eof()) {
		throw FileFormatError("Archivo vacio: "s + map);
	}

	// Variables auxiliares para la creaci�n de los objetos
	int elementType,
		elementX,
		elementY,
		subIndiceAlien,
		lifes,
		cooldown,
		state,
		points;

	// Lectura
	if (entrada.is_open()) {
		while (entrada) {
			// Lectura de l�nea
			entrada >> elementType;

			// Si leemos un player --> Asignaci�n del player
			if (elementType == 0) {

				entrada >> elementX;
				entrada >> elementY;
				entrada >> lifes;
				entrada >> cooldown;
				Cannon* c = new Cannon(this, textures[Spaceship], Point2D<int>(elementX, elementY),
					textures[Spaceship]->getFrameWidth(), textures[Spaceship]->getFrameHeight(), lifes, 0, 0, cooldown);
				objectElems.push_back(c);
				player = c;
			}

			// Si leemos un alien --> Asignamos el alien
			else if (elementType == 1) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> subIndiceAlien;
				Alien* a = new Alien(this, textures[Aliens], Point2D<int>(elementX, elementY),
					textures[Aliens]->getFrameWidth(), textures[Aliens]->getFrameHeight(), 1, subIndiceAlien, 0, mama);
				objectElems.push_back(a);
				mama->addAlien();
			}

			// Si leemos un alien disparador --> Asignamos el alien disparador
			else if (elementType == 2) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> subIndiceAlien;
				entrada >> cooldown;
				ShooterAlien* a = new ShooterAlien(this, textures[Aliens], Point2D<int>(elementX, elementY),
					textures[Aliens]->getFrameWidth(), textures[Aliens]->getFrameHeight(), 1, subIndiceAlien, 0, mama, cooldown);
				objectElems.push_back(a);
				mama->addAlien();
			}

			// Si leemos un b�nker --> Asignamos el b�nker
			else if (elementType == 4) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> lifes;
				Bunker* b = new Bunker(this, textures[Bunkers], Point2D<int>(elementX, elementY),
					textures[Bunkers]->getFrameWidth(), textures[Bunkers]->getFrameHeight(), lifes, 0, 0);
				objectElems.push_back(b);
			}

			// Si leemos un UFO --> Asignamos el UFO
			else if (elementType == 5) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> state;
				entrada >> cooldown;
				UFO* b = new UFO(this, textures[UFOs], Point2D<int>(elementX, elementY),
					textures[UFOs]->getFrameWidth(), textures[UFOs]->getFrameHeight(), 1, 0, 0, state, cooldown);
				objectElems.push_back(b);
			}

			// Si leemos la Mothership --> Asignamos la Mothership
			else if (elementType == 3) {
				entrada >> cooldown;
				mama->SetMothership(0, cooldown);
			}

			// Si leemos la puntuaci�n --> Asignamos puntos
			else if (elementType == 8) {
				entrada >> points;
				myPoints = points;
			}

			// Si leemos 7 --> No hacemos nada
			else if (elementType == 7) {
				entrada >> cooldown;
			}
		}

		// Asignamos a cada sceneObject su iterador
		std::list<SceneObject*>::iterator it = objectElems.begin();
		for (SceneObject* s : objectElems) {
			s->setListIterator(it);
			++it;
		}
	}

	// Cierre de flujo
	entrada.close();
}

// Cuando un objeto ha de ser eliminado se a�ade a la lista de objetos a eliminar
void SDLApplication::HasDied(const std::list<SceneObject*>::iterator& it) {
	if (it != objectElems.end()) {
		objectToDelete.push_back(*it);
	}
}

// Devuelve el n�mero de aliens
int SDLApplication::GetAlienNums() {
	int auxAlienNum = 0;
	for (list<SceneObject*>::iterator it = objectElems.begin(); it != objectElems.end(); ++it) {
		if (dynamic_cast<Alien*>(*it) != nullptr) {
			auxAlienNum++;
		}
	}
	return auxAlienNum;
}

// Suma los puntos recibidos a la puntuaci�n general
void SDLApplication::addPoints(int p) {
	myPoints += p;
}

// Guardado en un archivo k
void SDLApplication::Save(int k) {
	string fileName = "saved";

	// Creaci�n del flujo
	ofstream out(fileName + to_string(k) + ".txt");

	// Cada sceneObject se guarda con los datos necesarios en el flujo
	for (auto i : objectElems) {
		i->Save(out);
	}
	// Guardado de la mothership
	mama->Save(out);

	// Guardado de los puntos
	out << 8 << " ";
	out << myPoints << "\n";

	// Cerramos flujo
	out.close();
}