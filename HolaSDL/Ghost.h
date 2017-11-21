#ifndef _H_GHOST_H_
#define _H_GHOST_H_
#include "Texture.h"
#include <stdlib.h>
class Game;
class Ghost
{
public:
	Ghost(Game* g, int x, int y);
	~Ghost();

	void update();
	void render(int g);
private:

	int _x;
	int _y;
	Game* pGame;
	SDL_Rect _rect;
	Texture* gText;
	void move(int m);
};

#endif