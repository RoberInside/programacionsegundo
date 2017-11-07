#ifndef _H_PACMAN_H_
#define _H_PACMAN_H_
#include "Character.h"
class Game; //evitar recursion ciclica

class Pacman :
	public Character
{
public:
	Pacman(int x, int y);
	~Pacman();

private:
	Direction controller();
};

#endif