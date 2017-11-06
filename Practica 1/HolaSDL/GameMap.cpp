#include "GameMap.h"


GameMap::GameMap(size_t rows, size_t cols)
{
	_rows = rows;
	_cols = cols;
}


GameMap::~GameMap()
{
	for (size_t i = 0; i < _rows*_cols; i++)
	{
		delete board[i].obj;
		board[i].obj = nullptr;
	}
	delete board;
	board = nullptr;
}

void GameMap::setAt(GameObject * object, size_t x, size_t y)
{
	board[x*_cols + y].obj = object;
}
