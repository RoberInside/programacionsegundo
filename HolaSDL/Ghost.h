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

	int getX() const { return _y; }
	int getY() const { return _x; }
	
	void kill();

	bool isAlive() { return alive; }
private:
	bool alive;
	bool supermode;
	char color;
	int ss_col, ss_row;
	int _x;
	int _y;
	Game* pGame;
	SDL_Rect _rect;
	Texture* gText;
	void move();
};

#endif