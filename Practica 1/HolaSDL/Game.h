#ifndef _H_GAME_H_
#define _H_GAME_H_
#pragma once
#include <SDL.h>
#include <vector>
#include "Position.h"
#include "Pacman.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameMap.h"
#include "Food.h"
#include "Vitamin.h"
#include <string>
#include <iostream>
#include <fstream>
#define MAX_TICKS_PER_SECOND 2
#define MAX_LEVELS

using Direction = Position;

using namespace std;

class Game
{

public:
	Game();
	~Game();
	void run();

	Direction getNextDirection() {
		return nextDir; 
	};
	bool playerCollision(GameObject::ObjectType &type);
	SDL_Renderer* getRenderer() {
		return pRenderer;
	}
	void rectToTile(SDL_Rect& rawRect);
private:
	bool initSDL();
	bool closeSDL();
	bool initBoard(string path);
	void setTileSize(SDL_Rect& rawTile);
	/*bool saveBoard(string path);*/

	bool initMedia();
	bool freeMedia();
	//bool freeBoard();

	void render();
	void update(Uint32 delta);
	void handleEvents();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	size_t winWidth = 800;
	size_t winHeight = 600;
	bool exit = false;
	vector <GameObject*> gameObjects;
	vector <string> pathToLevels;
	size_t currentLevel;
	GameObject* pacman;
	GameMap* gameMap;
	Direction nextDir;
	SDL_Event e;
	SDL_Rect tile;
	SDL_Renderer* pRenderer;

};
#endif // !_H_GAME_H_


