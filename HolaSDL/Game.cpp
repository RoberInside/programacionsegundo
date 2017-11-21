#include "Game.h"


Game::Game()
{
	exit = false;
	currentLevel = 1;
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
	return gameMap->isEmpty(x, y);// && !tiGhost(x, y);
}

bool Game::tiGhost(int x, int y)
{



	return true;
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
	
	for (size_t i = 0; i < 4; i++)
	{
	delete ghosts[i];
	}
	
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
				
			}
			else if (buffer == '4') { //si no ponia empty no salian del cuadrado
				gameMap->setAt(MapCell_t::Empty, i, j);
			}
			else if (buffer == '5') {
				gameMap->setAt(MapCell_t::Empty, i, j);
				ghosts[0] = new Ghost(this, i, j, 0);
				
			}
			else if (buffer == '6') {
				gameMap->setAt(MapCell_t::Empty, i, j);
				ghosts[1] = new Ghost(this, i, j, 1);

			}
			else if (buffer == '7') {
				gameMap->setAt(MapCell_t::Empty, i, j);
				ghosts[2] = new Ghost(this, i, j, 2);

			}
			else if (buffer == '8') {
				gameMap->setAt(MapCell_t::Empty, i, j);
				ghosts[3] = new Ghost(this, i, j, 3);

			}		
			else if (buffer == '9') {
				gameMap->setAt(MapCell_t::Empty, i, j);
				pacman = new Pacman(this, i, j);
			}
				
				
			}
		}
	
	return true;
}

void Game::run() {

	Uint32 lastFrame;
	Uint32 lastUpdate = lastFrame = 1;
	Uint32 deltaUpdate, deltaFrame;
#ifdef DEBUG
	int cont = 0;
#endif // DEBUG
	while (!exit) {
#ifdef DEBUG
		system("cls");
#endif // DEBUG

		deltaUpdate = SDL_GetTicks() - lastUpdate;
		deltaFrame = SDL_GetTicks() - lastFrame;

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
		cout << "Frame " << cont << endl
			<< "dUpdate: " << deltaUpdate << endl
			<< "dFrame " << deltaFrame << endl;
		cont++;
#endif // DEBUG
	}
}
void Game::update()
{
	pacman->update();
	
	for (auto g : ghosts) {
	g->update();
	}
	
}
void Game::render()
{
	SDL_RenderClear(renderer);
	
	gameMap->render();
	pacman->render();
	for (int i = 0; i < 4; i++) ghosts[i]->render();
	
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
					initBoard(pathToLevels[currentLevel]);
				}
				break;
			case SDLK_MINUS:
				if (currentLevel > 0) {
					currentLevel--;
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
