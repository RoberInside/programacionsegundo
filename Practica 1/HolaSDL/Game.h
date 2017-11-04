#ifndef _H_GAME_H_
#define _H_GAME_H_
#pragma once
#include <SDL.h>
#include <vector>

#include "Texture.h"
#include "GameObject.h"
#include "GameMap.h"
#include "MapCell.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	size_t winWidth = 800;
	size_t winHeight = 600;
	bool exit = false;
	vector <GameObject*> gameObjects;
	GameMap* gameMap;

public:
	Game();
	~Game();
	void run();
private:
	bool initSDL();
	bool closeSDL();
	bool initBoard(string path);
	bool saveBoard(string path);

	bool initMedia();
	bool freeMedia();
	bool freeBoard();

	void render();
	void update(Uint32 delta);
	void handleEvents();


};
#endif // !_H_GAME_H_


