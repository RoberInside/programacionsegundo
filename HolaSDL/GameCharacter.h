#ifndef _H_GAME_CHARACTER_H_
#define _H_GAME_CHARACTER_H_
#pragma once
#include "GameObject.h"

class GameCharacter: public GameObject
{
public:
	GameCharacter();
    virtual ~GameCharacter();

	inline int getPosX() const { return posActX; };
	inline int getPosY() const { return posActY; };

	virtual void render();


protected:
	int posIniX, posIniY; // posIniX = _x, posIniY = _y
	int posActX,  posActY; //esto no lo usamos
	int dirX, dirY; // esto no lo usamos 
	SDL_Rect _rect;
	Texture* text;
};
#endif // _H_GAME_CHARACTER_H_
