#include "Game.h"


Game::Game()
{
	exit = false;
	currentLevel = 0;
	initSDL();
	initMedia();
	initBoard(pathToLevels[currentLevel]);//TODO: poner una ruta por defecto, implementar un mapa
}

Game::~Game()
{
	freeMedia();
	closeSDL();
}

//Auxiliar function///
void Game::setTileSize(size_t rows, size_t cols) {
	tile.x = tile.y = 0;
	tile.w = winWidth / cols + 1; // aqui tambien se ve que suda de las cols y rows que le damos y sino pongo esos numeros no se pinta en proporcion a la pantalla 
	tile.h = winHeight / rows + 1; // actual (800x600)
}


void Game::rectToTile(SDL_Rect & rawRect)
{
	rawRect.w = tile.w;
	rawRect.h = tile.h;
}

bool Game::canMoveTo(int x, int y)
{
	return gameMap->isEmpty(x, y);
}

string Game::getTextPath(Texture_t text)
{
	return texts_paths[text];
}

bool Game::initSDL()
{
	bool success = true;
	size_t winX, winY;	
	winX = winY = SDL_WINDOWPOS_CENTERED;	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		cout << "Error initializing SDL\n";
		success = false;
	}
	return success;
}
void Game::closeSDL()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

bool Game::initMedia()
{
	pathToLevels = {
		"..\\maps\\test1.dat"
	};//TODO
	texts_paths.resize(9);
	texts_paths[tWall] = "..\\images\\wall.png";
	texts_paths[tPacman] = "..\\images\\pacman.png";
	texts_paths[tGhost1] = "..\\images\\ghost1.png";
	texts_paths[tGhost2] = "..\\images\\ghost2.png";
	texts_paths[tGhost3] = "..\\images\\ghost3.png";
	texts_paths[tGhost4] = "..\\images\\ghost4.png";
	texts_paths[tFood] = "..\\images\\food.png";
	texts_paths[tVitamin] = "..\\images\\vitamin.png";
	texts_paths[tEmpty] = "..\\images\\empty.png";
	return true;
}
void Game::freeMedia()
{
	delete gameMap;
	delete pacman;
	/*
	for (size_t i = 0; i < 4; i++)
	{
		delete ghosts[i];
	}
	*/
}

bool Game::initBoard(string path){
	
	ifstream in(path);
	char buffer;
	size_t rows, cols, ghost_count = 0;
	in >> rows >> cols;
	setTileSize(rows, cols);
	gameMap = new GameMap(this, rows + 2, cols +1); // rows +2 wtff?? es como si no cogiese todas las rows que se le asignan y si pongo cols + 1 el level01 se pinta bien, no entiendo una puta mierda xddd
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			in >> buffer;
			if (buffer == '0'){
				gameMap->setAt(MapCell_t::Empty, j, i); //estaban la i y la j al reves
			}else if (buffer == '1'){
				gameMap->setAt(MapCell_t::Wall, j, i);
			}else if (buffer == '2'){
				gameMap->setAt(MapCell_t::Food, j, i);
			}else if (buffer == '3'){
				gameMap->setAt(MapCell_t::Vitamins, j, i);
				//no esta asignado el 4 para la puerta del recinto de los fantasmas
			}else if (buffer == '9'){
				gameMap->setAt(MapCell_t::Empty, j, i);
				pacman = new Pacman(this, j, i);
			}else if (buffer == '5' || buffer == '6' || buffer == '7' || buffer == '8'){
				gameMap->setAt(MapCell_t::Empty, j, i);
				//ghosts[ghost_count];
				ghost_count++;
			}
		}
	}
	return true;
}

void Game::run() {

	Uint32 delta;
	Uint32 lastUpdate = SDL_GetTicks();
	while (!exit) {
		delta = SDL_GetTicks() - lastUpdate;
		//update();
		lastUpdate = SDL_GetTicks();
		render();
		handleEvents();
	}
}
void Game::update()
{
	pacman->update();
	/*
	for (auto g : ghosts) {
		g->update();
	}
	*/
}
void Game::render()
{
	SDL_RenderClear(renderer);
	
	gameMap->render();
	//pacman->render();
	//for (Ghost* g : ghosts) g->update();

	SDL_RenderPresent(renderer);
}
void Game::handleEvents()
{
	while (SDL_PollEvent(&e) && !exit)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYUP:
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				nextDir = Direction::UP;
				break;
			case SDLK_DOWN:
				nextDir = Direction::DOWN;
				break;
			case SDLK_RIGHT:
				nextDir = Direction::RIGHT;
				break;
			case SDLK_LEFT:
				nextDir = Direction::LEFT;
				break;
			case SDLK_ESCAPE:
				exit = true;
			default:
				break;
			}
		}
	}
}