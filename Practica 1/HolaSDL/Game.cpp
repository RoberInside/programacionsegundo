#include "Game.h"


Game::Game()
{
	initSDL();
	initMedia();	
}


Game::~Game()
{
	freeMedia();
	closeSDL();
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

}
bool Game::freeMedia()
{

}

bool Game::initBoard(string path){
	
	
	ifstream in(path);
	char buffer;
	int rows, cols;
	in >> rows >> cols;
	gameMap = new GameMap(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			in >> buffer;
			if (buffer == 0){}
			else if (buffer == 1){
				gameMap->at(i, j);
			}else if (buffer == 2){
			}else if (buffer == 3){
			}else if (buffer == 9){
			}else if (buffer == 5 || buffer == 6 || buffer == 7 || buffer == 8){
			}
		}
	}
	
}
bool Game::freeBoard(){}
bool Game::saveBoard(string path){

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



}
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
	//nos falta saber los estados
}
void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
void Game::handleEvents()
{

}
