#ifndef _H_GAME_H_
#define _H_GAME_H_
#pragma once
#include <SDL.h>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>

#include "Pacman.h"
#include "Texture.h"
#include "Ghost.h"
#include "GameMap.h"
#include "SmartGhost.h"
#include "FileSystem.h"

#define DEBUG
#define MAX_TICKS_PER_SECOND 3
#define	FPS 6
#define NUM_TEXTURES 4

using namespace std;

inline string format(string s) { return s + ".pac"; };

class Game
{

public:
	Game();
	~Game();
	void run();

	enum Texture_t {
		tWall = 0,		
		tVitamin = 1,
		tPjes = 2,
		tFood = 3
		
	};
	enum class Direction{UP = 3, DOWN = 1, RIGHT = 0, LEFT = 2};
	void rectToTile(SDL_Rect & rawRect);
	SDL_Renderer* getRenderer() { return renderer; }
	Direction getNextDir() { return nextDir; }
	inline Texture* getTexture(Texture_t type) {
		return textures[type]; 
	};
	bool canMoveTo(int x, int y);
	string getTextPath(Texture_t text);

	inline FileSystem* getFileSystem() { return fileSystem; }
private:
	bool initSDL();
	void closeSDL();
	bool initObjects(string path);
	void setTileSize(size_t rows, size_t cols);

	bool initMedia();
	void freeMedia();

	void render();
	void update();
	void handleEvents();
	void checkCollisions();
	void killPacman();
	void reset();
#ifdef DEBUG
	void showDebugInfo();
#endif // DEBUG

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	size_t winWidth = 800;
	size_t winHeight = 600;
	bool exit = false;
	vector <string> pathToLevels;
	vector <string> texts_paths;
	vector <Texture*> textures;
	list <GameCharacter*> objects;
	size_t currentLevel;
	FileSystem* fileSystem;
	GameMap* gameMap;
	Pacman* pacman;
	Direction nextDir;
	SDL_Event e;
	SDL_Rect tile;
	Ghost* ghosts[4];
	int level;
	int score;
	const int foodPoints;
	const int vitaminPoints;
};
#endif // !_H_GAME_H_


