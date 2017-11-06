#ifndef _H_PACMAN_H_
#define _H_PACMAN_H_
#include "Character.h"
class Pacman :
	public Character
{
public:
	Pacman(int x, int y);
	~Pacman();
};

#endif