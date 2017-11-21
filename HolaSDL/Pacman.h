#ifndef _H_PACMAN_H_
#define _H_PACMAN_H_
#include "Texture.h"
class Game; //evitar recursion ciclica

class Pacman
{
public:
	Pacman(Game* g, int x, int y);
	~Pacman();

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
	Texture* pacText;
	void move();
	


};

#endif