#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(int x, int y)
{
	_type = ObjectType::Pacman;
	pos = { x, y };

}


Pacman::~Pacman()
{
}
