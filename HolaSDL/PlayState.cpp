#include "checkML.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include "Mothership.h"

const std::string PlayState::s_playID = "PLAY";

// Constructora
PlayState::PlayState(SDLApplication* app) : GameState(app), rdo(mt19937_64(time(nullptr))) {
	mama = new Mothership(this);
	LoadMaps("original.txt");
	//Menu();
}

// Destructora
PlayState::~PlayState() {
	//for (auto i : objectElems) delete i;
	delete mama;

	/*SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();*/
}

// Menu de incio
void PlayState::Menu() {
	int res;
	cout << "Pulse los siguientes números para cargar los mapas \n";
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
void PlayState::Run() {
	// Mientras el jugador este vivo o no hayan muerto todos los aliens
	while (!exit) {

		//SDL_RenderClear(renderer);
		Update();
		Render();
		//HandleEvent();
	}

	cout << "A POR EL SPACE INVADERS 3.0";
};

// Render general
void PlayState::Render() const {
	getGame()->getTexture(TextureName::Stars)->render();

	// Renderizado de todos los objetos de escena
	for (GameObject& obj : myList) {
		obj.Render();
	}
	// Renderizado de la puntuación
	//RenderPoints();

	//SDL_RenderPresent(renderer);
}

// Render de los puntos
void PlayState::RenderPoints() {
	SDL_Rect scoreRect = { 0, 550, 50, 50 };
	getGame()->getTexture(TextureName::Numbers)->renderFrame(scoreRect, 0, (myPoints / 1000) % 1000);
	scoreRect = { 50, 550, 50, 50 };
	getGame()->getTexture(TextureName::Numbers)->renderFrame(scoreRect, 0, (myPoints / 100) % 100);
	scoreRect = { 100, 550, 50, 50 };
	getGame()->getTexture(TextureName::Numbers)->renderFrame(scoreRect, 0, (myPoints / 10) % 10);
	scoreRect = { 150, 550, 50, 50 };
	getGame()->getTexture(TextureName::Numbers)->renderFrame(scoreRect, 0, 0);
}

// Update general
void PlayState::Update() {
	// Update de los scenesObjects
	for (GameObject& obj : myList) {
		obj.Update();
	}
	// Lista auxiliar para eliminar los objetos
	/*for (auto i : objectToDelete) {
		objectElems.erase(i->getIterator());
		delete i;
	}*/

	/*if (objectToDelete.size() > 0) {
		objectToDelete.clear();
	}*/

	// Actualización del update de la mothership
	mama->Update();
	if (pop) getGame()->ReplaceState(new EndState(getGame()));
}

// Manejo de eventos
void PlayState::HandleEvent(const SDL_Event& event)
{
	if (!getGame()->GetExit())
	{
		if (pause)
		{
			if (event.type == SDL_KEYDOWN)
			{
				// Cuando es un número válido para guardar archivo
				if (event.key.keysym.sym > 47 && event.key.keysym.sym < 58)
				{
					if (saving)
					{
						// Guardamos en el número determinado
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
					cout << "Número de archivo: ";
					pause = true;
					saving = true;
				}
				else if (event.key.keysym.sym == SDLK_l)
				{
					system("cls");
					cout << "Número de archivo: ";
					pause = true;
					saving = false;
				}
			}
		}
		if (event.type == SDL_QUIT) {
			getGame()->SetExit();
		}
	}
}

// Disparar
void PlayState::FireLaser(Point2D<int> position, const char* color) {
	// Creamos el laser y se añade al vector
	Laser* l = new Laser(this, this, nullptr, position, 10, 20, 1, 0, 0, color);
	addObject(l);
	objectElems.push_back(l);
	//l->setListIterator(prev(objectElems.end()));
}

void PlayState::SpawnUFO() {
	Texture* auxTex = getGame()->getTexture(TextureName::UFOs);
	UFO* u = new UFO(this, this, auxTex, Vector2D<int>(800, 10), auxTex->getFrameWidth(), auxTex->getFrameHeight(), 1, 0, 0, 0, 200);
	addObject(u);
	objectElems.push_back(u);
	//u->setListIterator(prev(objectElems.end()));
}

// Generador de aleatorios
int PlayState::GetRandomRange(int min, int max) {
	return 1;
	//return uniform_int_distribution<int>(min, max)(rdo);
}

// Colisiones
bool PlayState::Damage(SDL_Rect rect, const char* c) {
	/*for (auto it = objectElems.begin(); it != objectElems.end(); ++it) {
		if ((*it).Hit(rect, c)) return true;
	}*/
	for (SceneObject& obj : objectElems) {
		if (obj.Hit(rect, c)) return true;
	}
	return false;
}

// Carga de mapas
void PlayState::LoadMaps(string map) {
	// Flujo de entrada
	ifstream entrada(map);

	if (!entrada.is_open()) {
		throw FileNotFoundError("Error archivo no encontrado: "s + map);
	}

	if (entrada.peek() == ifstream::traits_type::eof()) {
		throw FileFormatError("Archivo vacio: "s + map);
	}

	// Variables auxiliares para la creación de los objetos
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
			// Lectura de línea
			entrada >> elementType;

			// Si leemos un player --> Asignación del player
			if (elementType == 0) {

				entrada >> elementX;
				entrada >> elementY;
				entrada >> lifes;
				entrada >> cooldown;
				Texture* auxTex = getGame()->getTexture(TextureName::Spaceship);
				Cannon* c = new Cannon(this, this, auxTex, Point2D<int>(elementX, elementY),
					auxTex->getFrameWidth(), auxTex->getFrameHeight(), lifes, 0, 0, cooldown);
				myList.push_back(c);
				objectElems.push_back(c);
				player = c;
			}

			// Si leemos un alien --> Asignamos el alien
			else if (elementType == 1) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> subIndiceAlien;
				Texture* auxTex = getGame()->getTexture(TextureName::Aliens);
				Alien* a = new Alien(this, this, auxTex, Point2D<int>(elementX, elementY),
					auxTex->getFrameWidth(), auxTex->getFrameHeight(), 1, subIndiceAlien, 0, mama);
				myList.push_back(a);
				objectElems.push_back(a);
				mama->addAlien();
			}

			// Si leemos un alien disparador --> Asignamos el alien disparador
			else if (elementType == 2) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> subIndiceAlien;
				entrada >> cooldown;
				Texture* auxTex = getGame()->getTexture(TextureName::Aliens);
				ShooterAlien* a = new ShooterAlien(this, this, auxTex, Point2D<int>(elementX, elementY),
					auxTex->getFrameWidth(), auxTex->getFrameHeight(), 1, subIndiceAlien, 0, mama, cooldown);
				myList.push_back(a);
				objectElems.push_back(a);
				mama->addAlien();
			}

			// Si leemos un búnker --> Asignamos el búnker
			else if (elementType == 4) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> lifes;
				Texture* auxTex = getGame()->getTexture(TextureName::Bunkers);
				Bunker* b = new Bunker(this, this, auxTex, Point2D<int>(elementX, elementY),
					auxTex->getFrameWidth(), auxTex->getFrameHeight(), lifes, 0, 0);
				myList.push_back(b);
				objectElems.push_back(b);
			}

			// Si leemos un UFO --> Asignamos el UFO
			else if (elementType == 5) {
				entrada >> elementX;
				entrada >> elementY;
				entrada >> state;
				entrada >> cooldown;
				Texture* auxTex = getGame()->getTexture(TextureName::UFOs);
				UFO* b = new UFO(this, this, auxTex, Point2D<int>(elementX, elementY),
					auxTex->getFrameWidth(), auxTex->getFrameHeight(), 1, 0, 0, state, cooldown);
				myList.push_back(b);
				objectElems.push_back(b);
			}

			// Si leemos la Mothership --> Asignamos la Mothership
			else if (elementType == 3) {
				entrada >> cooldown;
				mama->SetMothership(0, cooldown);
			}

			// Si leemos la puntuación --> Asignamos puntos
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
		auto it = objectElems.begin();
		for (SceneObject& s : objectElems) {
			//s.setListIterator(it);
			++it;
		}
	}

	// Cierre de flujo
	entrada.close();
}

// Cuando un objeto ha de ser eliminado se añade a la lista de objetos a eliminar
void PlayState::HasDied(GameList<SceneObject, false>::anchor it) {
	objectElems.erase(it);
}

// Devuelve el número de aliens
int PlayState::GetAlienNums() {
	int auxAlienNum = 0;
	for (auto it = objectElems.begin(); it != objectElems.end(); ++it) {
		/*if (dynamic_cast<Alien*>(*it) != nullptr) {
			auxAlienNum++;
		}*/
	}
	return auxAlienNum;
}

// Suma los puntos recibidos a la puntuación general
void PlayState::addPoints(int p) {
	myPoints += p;
}

// Guardado en un archivo k
void PlayState::Save(int k) {
	string fileName = "saved";

	// Creación del flujo
	ofstream out(fileName + to_string(k) + ".txt");

	// Cada sceneObject se guarda con los datos necesarios en el flujo
	for (SceneObject &obj : objectElems) {
		obj.Save(out);
	}
	// Guardado de la mothership
	mama->Save(out);

	// Guardado de los puntos
	out << 8 << " ";
	out << myPoints << "\n";

	// Cerramos flujo
	out.close();
}