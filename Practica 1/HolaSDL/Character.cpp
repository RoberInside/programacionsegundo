#include "Character.h"


Character::Character(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Character::update()
{
	controller();
}

void Character::draw()
{
	//TODO
}

void Character::move(Position pos)
{
	if (!collision(pos)) 
		this->pos = pos;
}

bool Character::collision(Position target)
{
	//TODO
	return false;
}

