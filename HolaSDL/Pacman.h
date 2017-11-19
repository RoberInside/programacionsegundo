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
private:
	int _x;
	int _y;
	int _col, _row;
	Game* pGame;
	SDL_Rect _rect;
	Texture* texture;
	void move();


};

#endif