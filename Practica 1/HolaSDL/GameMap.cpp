#include "GameMap.h"


GameMap::GameMap(size_t rows, size_t cols)
{
	_rows = rows;
	_cols = cols;
}


GameMap::~GameMap()
{
}

void GameMap::setAt(MapCell_t type, size_t x, size_t y)
{
	board[x][y] = type;
}

bool GameMap::isAt(MapCell_t type, size_t x, size_t y)
{
	return board[x][y] == type;
}

bool GameMap::isEmpty(size_t x, size_t y)
{
	return board[x][y] == Empty;
}

bool GameMap::isEmpty(Position pos)
{
	return isEmpty(pos.x, pos.y);
}


