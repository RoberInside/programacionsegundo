#include "Food.h"



Food::Food(int x, int y) {
	this->pos = { x, y };
}
Food::Food(Position pos)
{
	this->pos = pos;
}


Food::~Food()
{
}
void Food::render() {}