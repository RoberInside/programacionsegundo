#include "Game.h"


Game::Game()
{
	exit = false;
	currentLevel = 0;
	initSDL();
	initMedia();
	initBoard(pathToLevels[currentLevel]);//TODO: poner una ruta por defecto, implementar un mapa
	setTileSize(tile);
}

Game::~Game()
{
	freeMedia();
	closeSDL();
}

//Auxiliar function///
void Game::setTileSize(SDL_Rect &rawTile) {
	rawTile.w = winWidth / gameMap->getRows();
	rawTile.h = winHeight / gameMap->getCols();
}

bool Game::playerCollision(GameObject::ObjectType &type)
{
	bool collision = false;
	int i = 1;
	while (!collision && i < gameObjects.size()) {
		collision = pacman->getPosition() == gameObjects[i]->getPosition();
	}
	if (collision) type = gameObjects[i]->getType();
	return collision;
}

void Game::rectToTile(SDL_Rect & rawRect)
{
	rawRect.w = tile.w;
	rawRect.h = tile.h;
}

bool Game::initSDL()
{
	bool success = false;
	size_t winX, winY;	
	winX = winY = SDL_WINDOWPOS_CENTERED;	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		cout << "Error	initializing	SDL\n";
		success = true;
	}
	else success = false;

		return success;
}
bool Game::closeSDL()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

bool Game::initMedia()
{
	pathToLevels = {""};//TODO

}
bool Game::freeMedia()
{
	for (auto o : gameObjects)
		delete o;
}

bool Game::initBoard(string path){
	
	
	ifstream in(path);
	char buffer;
	int rows, cols;
	in >> rows >> cols;
	gameMap = new GameMap(rows, cols);
	//Every game has only a Pacman, for simplycity the first object in array will always be the player
	gameObjects.push_back(pacman);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			in >> buffer;
			if (buffer == '0'){
				gameMap->setAt(Empty, i, j);
			}else if (buffer == '1'){
				gameMap->setAt(Wall, i, j);
			}else if (buffer == '2'){
				gameMap->setAt(Foods, i, j);
				gameObjects.push_back(new Food(i, j));
			}else if (buffer == '3'){
				gameMap->setAt(Vitamins, i, j);
				gameObjects.push_back(new Vitamin(i, j));
			}else if (buffer == '9'){
				gameMap->setAt(Empty, i, j);
				pacman = new Pacman(i, j);
			}else if (buffer == '5' || buffer == '6' || buffer == '7' || buffer == '8'){
				gameMap->setAt(Empty, i, j);
				//gameObjects.push_back(new Ghost(i, j))
			}
		}
	}
	
}
//bool Game::freeBoard(){}
/*bool Game::saveBoard(string path){

	fstream out(path, ios::out);
	for (size_t i = 0; i < gameMap->getRows(); i++)
	{
		for (size_t j = 0; j < gameMap->getCols(); j++)
		{
			out << gameMap->at(i, j)<<" ";
		}
		out << endl;
	}
	out.close();



}*/
void Game::run() {

	Uint32 delta;
	Uint32 lastUpdate = SDL_GetTicks();
	while (!exit) {
		delta = SDL_GetTicks() - lastUpdate;
		update(delta);
		lastUpdate = SDL_GetTicks();
		render();
		handleEvents();
	}
}
void Game::update(Uint32 delta)
{
	for(auto o : gameObjects)
		o->update();
}
void Game::render()
{
	SDL_RenderClear(renderer);

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
				nextDir = Direction{ 0, 1 };
				break;
			case SDLK_DOWN:
				nextDir = Direction{ 0, -1 };
				break;
			case SDLK_RIGHT:
				nextDir = Direction{ 1, 0 };
				break;
			case SDLK_LEFT:
				nextDir = Direction{ -1, 0 };
				break;
			case SDLK_ESCAPE:
				exit = true;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		default:
			break;
		}
	}

}
