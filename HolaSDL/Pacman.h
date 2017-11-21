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

	int getX() const { return _y; }
	int getY() const { return _x; }

	void setSuperMode() { superMode = true; };
	bool isSuperMode() { return superMode; }
private:
	int ss_col, ss_row;

	bool superMode;
	int _x;
	int _y;
	Game* pGame;
	SDL_Rect _rect;
	Texture* pacText;
	void move();
	


};

#endif