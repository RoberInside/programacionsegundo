#include "Vitamin.h"



Vitamin::Vitamin(int x, int y)
{
	this->pos = { x, y };
}

Vitamin::Vitamin(Position pos)
{
	this->pos = pos;
}


Vitamin::~Vitamin()
{
}

void Vitamin::update() {}