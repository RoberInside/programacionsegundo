#include "Game.h"


Game::Game()
{
	exit = false;
	currentLevel = 0;
	nextDir = Direction::RIGHT;
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
/*	Brief
*	Returns true if pacman can move to the square in the params
*	Also, if true, return the next avaliable position by params reference
*/
bool Game::canMoveTo(int& x, int& y)
{
	int x_ = x, y_ = y;
	if (x_ >= gameMap->getCols() && y < gameMap->getRows() && gameMap->isEmpty(0, y_)) {
		x = 0;
		return true;
	}
	if (x_ < 0 && y_ < gameMap->getRows() && gameMap->isEmpty(gameMap->getCols()-1, y_)) {
		x = gameMap->getCols() - 1;
		return true;
	}
	if (x_ < gameMap->getCols() && y >= gameMap->getRows() && gameMap->isEmpty(x_, 0)) {
		y = 0;
		return true;
	}
	if (x_ < gameMap->getCols() && y_ < 0 && 
		gameMap->isEmpty(x_, gameMap->getRows()-1)) 
	{
		y = gameMap->getRows() - 1;
		return true;
	}
	return gameMap->isEmpty(x_, y_);
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
	texts_paths[tFood] = "..\\images\\food.png";
	
	//Init Textures
	textures.resize(NUM_TEXTURES);
	textures[tWall] = new Texture();
	textures[tWall]->load(getRenderer(), texts_paths[tWall]);
	textures[tVitamin] = new Texture();
	textures[tVitamin]->load(getRenderer(), texts_paths[tVitamin]);
	textures[tPjes] = new Texture(4, 14);
	textures[tPjes]->load(getRenderer(), texts_paths[tPjes]);
	textures[tFood] = new Texture();
	textures[tFood]->load(getRenderer(), texts_paths[tFood]);
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
	size_t ghost_count = 0;
	in >> ROWS >> COLS;
	setTileSize(ROWS, COLS);

	gameMap = new GameMap(this, ROWS, COLS);

	for (size_t i = 0; i < ROWS; i++)
	{
		for (size_t j = 0; j < COLS; j++)
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
				pacman = new Pacman(this, i,j);
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
	Uint32 lastFrame;
	Uint32 lastUpdate  = lastFrame = 1;
	Uint32 deltaUpdate, deltaFrame;
#ifdef DEBUG
	int cont = 0;
#endif // DEBUG
	while (!exit) {
#ifdef DEBUG
		//system("cls");
#endif // DEBUG

		deltaUpdate = SDL_GetTicks() - lastUpdate;
		deltaFrame	= SDL_GetTicks() - lastFrame;

		if (deltaUpdate >= 1000 / MAX_TICKS_PER_SECOND) {
			update();
			lastUpdate = SDL_GetTicks();
		}
		if (deltaFrame >= 1000 / FPS) {
			render();
			lastFrame = SDL_GetTicks();
		}
		handleEvents();
#ifdef DEBUG
		/*cout<< "Frame "		<<  cont		<<	endl
			<< "dUpdate: "	<<	deltaUpdate	<<	endl
			<< "dFrame "	<<	deltaFrame	<<	endl;
		cont++;*/
#endif // DEBUG
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
	pacman->render();
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
#ifdef DEBUG
			case SDLK_PLUS:
				if (currentLevel < 5) {
					currentLevel++;
					delete gameMap;
					initBoard(pathToLevels[currentLevel]);
				}
				break;
			case SDLK_MINUS:
				if (currentLevel > 0) {
					currentLevel--;
					delete gameMap;
					initBoard(pathToLevels[currentLevel]);
				}
				break;
#endif // DEBUG
			default:
				break;
			}
		}
	}
}
