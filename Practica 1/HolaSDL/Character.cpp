#include "Character.h"


Character::Character()
{
}

void Character::update()
{
	controller();
}

void Character::draw()
{
	//TODO
}

void Character::move(Direction dir)
{
	Position last = pos;
	switch (dir)
	{
	case Direction::UP:
		pos += UP;
		break;
	case Direction::DOWN:
		pos += DOWN;
		break;
	case Direction::RIGHT:
		pos += RIGHT;
		break;
	case Direction::LEFT:
		pos += LEFT;
		break;
	default:
		break;
	}
	if (collision(pos)) pos = last;
}

bool Character::collision(Position target)
{
	//TODO
	return false;
}

