#ifndef _H_PACMAN_H_
#define _H_PACMAN_H_
#include "Texture.h"

const int superModeTime = 5 * 1000;//ms
class Game; //evitar recursion ciclica

class Pacman
{
public:
	Pacman(Game* g, int x, int y);
	~Pacman();

	void update();
	void render();

	inline int getX() const { return _y; }
	inline int getY() const { return _x; }

private:
	int ss_col, ss_row;

	int _x;
	int _y;
	Game* pGame;
	SDL_Rect _rect;
	Texture* pacText;
	void move();
	


};

#endif