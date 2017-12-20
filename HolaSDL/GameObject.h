#ifndef _H_GAME_OBJECT_H_
#define _H_GAME_OBJECT_H_	
#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class Texture; class Game;
class GameObject
{
public:

	GameObject() {}
	virtual ~GameObject() {}
	

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void loadFromFile() = 0;
	virtual void saveToFile() = 0;

protected:
	Game* pGame;
	FileSystem* fileSystem_ptr;
};
#endif //!_H_GAME_OBJECT_H_
