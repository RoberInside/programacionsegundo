#ifndef _H_GHOST_H_
#define _H_GHOST_H_
#include "Texture.h"
#include <stdlib.h>
class Game;
class Ghost
{
public:
	Ghost(Game* g, int x, int y, int color);
	~Ghost();

	void update();
	void render();

	int getX() const { return _x; }
	int getY() const { return _y; }
	
private:
	int ss_col, ss_row;
	int _x;
	int _y;
	Game* pGame;
	SDL_Rect _rect;
	Texture* gText;
	void move();
};

#endif