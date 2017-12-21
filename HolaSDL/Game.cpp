#include "Game.h"

Game::Game():exit(false), currentLevel(0), foodPoints(100), vitaminPoints(300)
{
	initSDL();
	initMedia();
	initObjects(pathToLevels[currentLevel]);//TODO: poner una ruta por defecto, implementar un mapa
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
	//Init font
	 TTF_Init();
	///////////
	pathToLevels = {
		"..\\maps\\level01.pac",
		"..\\maps\\level02.pac"
	};
	texts_paths.resize(NUM_TEXTURES);
	texts_paths[tWall] = "..\\images\\wall.png";
	texts_paths[tVitamin] = "..\\images\\vitamin.png";
	texts_paths[tPjes] = "..\\images\\characters1.png";
	texts_paths[tFood] = "..\\images\\food.png";
	texts_paths[tFont] = "..\\fonts\\third_rail.ttf";
	
	textures.resize(NUM_TEXTURES);
	textures[tWall] = new Texture();
	textures[tWall]->load(getRenderer(), texts_paths[tWall]);
	textures[tVitamin] = new Texture();
	textures[tVitamin]->load(getRenderer(), texts_paths[tVitamin]);
	textures[tPjes] = new Texture(4, 14);
	textures[tPjes]->load(getRenderer(), texts_paths[tPjes]);
	textures[tFood] = new Texture();
	textures[tFood]->load(getRenderer(), texts_paths[tFood]);
	//fuente
	textures[tFont] = new Texture();
	textures[tFont]->loadFuente(texts_paths[tFont], 300);
	
	fontColor.r = 250;
	fontColor.g = 1;
	fontColor.b = 1;

	
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

	//liberar fuente
	 TTF_Quit();

}

bool Game::initObjects(string path) {
	reset();
	fileSystem = new FileSystem(path);
	level = fileSystem->getGameData()->level;
	score = fileSystem->getGameData()->score;


	gameMap = new GameMap(this);
	pacman = new Pacman(this);
	characters.push_back(pacman);
	int ghostColor = 0;
	for (size_t i = 0; i < fileSystem->getGhostsData()->numGhosts; i++)
	{
		if (fileSystem->getGhostsData()->ghosts[i].type) {
			characters.push_back(new SmartGhost(this, i));
		}
		else {
			characters.push_back(new Ghost(this, i, ghostColor));
			ghostColor = (ghostColor+1) % 4;//We only have 4 normalGhost sprites, so we asset their sprite in range
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
	while (!exit) {//MAINLOOP////////////////////////////////
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
		//Debug variables in printed out console
		showDebugInfo();
#endif // DEBUG
	}//MAINLOOP/////////////////////////////////////////////
	//Game ended
#ifndef DEBUG//Just to not show every time we debug
	string finalInfo = "Your score is: " + to_string(score);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "GAME OVER", finalInfo.c_str(), window);
#endif // !DEBUG
}
void Game::update()
{
	for (GameCharacter* c : characters) {
		c->update();

	}
	checkCollisions();
	

}
void Game::render()
{
	SDL_RenderClear(renderer);
	
	gameMap->render();

	for (GameCharacter* c : characters) {
		c->render();
	}
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
					initObjects(pathToLevels[currentLevel]);
				}
				break;
			case SDLK_MINUS:
				if (currentLevel > 0) {
					currentLevel--;
					initObjects(pathToLevels[currentLevel]);
				}
				break;
#endif // DEBUG
			default:
				break;
			}
		}
	}
}

void Game::checkCollisions() {
	//Collisions with Ghosts
	auto it = characters.begin();
	it++;//As we know the pacman is the first node in the list
	for (;it != characters.end(); it++)
	{
		if (static_cast<Ghost*>(*it)->isAlive()) {
			if (pacman->getX() == (*it)->getPosX() &&
				pacman->getY() == (*it)->getPosY()) 
			{//Have been a collision
				if (static_cast<Ghost*>(*it)->isKilleable())
					static_cast<Ghost*>(*it)->kill();
				else
					killPacman();
			}
		}
	}
	//Collisions with food and vitamins
	if (!gameMap->isAt(MapCell_t::Wall, pacman->getX(), pacman->getY()) || !gameMap->isAt(MapCell_t::Empty, pacman->getX(), pacman->getY())) {
		// faltaba excluir que no fuesen empty
		if (gameMap->isAt(MapCell_t::Food, pacman->getX(), pacman->getY())) {
			
			score += foodPoints;
			
		}
		else if (gameMap->isAt(MapCell_t::Vitamins, pacman->getX(), pacman->getY())) {
			score += vitaminPoints;
			pacman->setSuperMode();
		}
		gameMap->setAt(MapCell_t::Empty, pacman->getX(), pacman->getY());
	}
	

}

void Game::killPacman()
{
	//Provisional!!
	if (pacman->kill()) {
		//fin del juego
	}	
}

void Game::reset()
{
}

#ifdef DEBUG
void Game::showDebugInfo()
{
	system("cls");
	cout
		<< "Pacman position: " << pacman->getX() << ", " << pacman->getY() << endl
		<< "Score: " << score << endl;
}

#endif // DEBUG
