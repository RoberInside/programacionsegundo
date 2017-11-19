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
	tile.w = winWidth / cols; 
	tile.h = winHeight / rows; 
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
		"..\\maps\\test1.dat",
		"..\\maps\\level01.dat",
		"..\\maps\\level02.dat",
		"..\\maps\\level03.dat",
		"..\\maps\\level04.dat",
		"..\\maps\\level05.dat"
	};
	texts_paths.resize(NUM_TEXTURES);
	texts_paths[tWall] = "..\\images\\wall.png";
	texts_paths[tVitamin] = "..\\images\\vitamin.png";
	texts_paths[tPjes] = "..\\images\\characters1.png";
	//texts_paths[tPjes] = "..\\images\\c.png";
	texts_paths[tFood] = "..\\images\\food.png";
	
	textures.resize(NUM_TEXTURES);
	textures[tWall] = new Texture();
	textures[tWall]->load(getRenderer(), texts_paths[tWall]);
	textures[tVitamin] = new Texture();
	textures[tVitamin]->load(getRenderer(), texts_paths[tVitamin]);
	textures[tPjes] = new Texture(4, 14);
	textures[tPjes]->load(getRenderer(), texts_paths[tPjes]);
	textures[tFood] = new Texture();
	textures[tFood]->load(getRenderer(), texts_paths[tFood]);
	//Init Textures
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

bool Game::initBoard(string path) {

	ifstream in(path);
	char buffer;
	size_t rows, cols, ghost_count = 0;
	in >> rows >> cols;
	setTileSize(rows, cols);

	gameMap = new GameMap(this, rows, cols); 

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			in >> buffer;

			if (buffer == '0') {
				gameMap->setAt(MapCell_t::Empty, i, j); 
			}
			else if (buffer == '1') {
				gameMap->setAt(MapCell_t::Wall, i, j);
			}
			else if (buffer == '2') {
				gameMap->setAt(MapCell_t::Food, i, j);
			}
			else if (buffer == '3') {
				gameMap->setAt(MapCell_t::Vitamins, i, j);
				//no esta asignado el 4 para la puerta del recinto de los fantasmas
			}
			else if (buffer == '9') {
				gameMap->setAt(MapCell_t::Empty, i, j);
				pacman = new Pacman(this, i, j);
			}
			else if (buffer == '5' || buffer == '6' || buffer == '7' || buffer == '8') {

				gameMap->setAt(MapCell_t::Empty, i, j);
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
