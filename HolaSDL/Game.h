#ifndef _H_GAME_H_
#define _H_GAME_H_
#pragma once
#include <SDL.h>
#include <vector>
#include "Pacman.h"
#include "Texture.h"
#include "Ghost.h"
#include "GameMap.h"
#include "Food.h"
#include "Vitamin.h"
#include <string>
#include <iostream>
#include <fstream>
#define MAX_TICKS_PER_SECOND 2

using namespace std;

class Game
{

public:
	Game();
	~Game();
	void run();

	enum Texture_t {
		tWall = 0,
		tPacman = 1,
		tGhost1 = 2,
		tGhost2 = 3,
		tGhost3 = 4,
		tGhost4 = 5,
		tFood = 6,
		tVitamin = 7,
		tEmpty = 8
	};
	enum class Direction{UP, DOWN, RIGHT, LEFT};
	void rectToTile(SDL_Rect & rawRect);
	SDL_Renderer* getRenderer() { return renderer; }
	Direction getNextDir() { return nextDir; }
	bool canMoveTo(int x, int y);
	string getTextPath(Texture_t text);
private:
	bool initSDL();
	void closeSDL();
	bool initBoard(string path);
	void setTileSize(size_t rows, size_t cols);

	bool initMedia();
	void freeMedia();

	void render();
	void update();
	void handleEvents();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	size_t winWidth = 800;
	size_t winHeight = 600;
	bool exit = false;
	vector <string> pathToLevels;
	vector <string> texts_paths;
	size_t currentLevel;
	//Ghost* ghosts[4] = { nullptr, nullptr, nullptr, nullptr };
	GameMap* gameMap;
	Pacman* pacman;
	Direction nextDir;
	SDL_Event e;
	SDL_Rect tile;

};
#endif // !_H_GAME_H_


