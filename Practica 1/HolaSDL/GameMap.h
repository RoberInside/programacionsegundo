#ifndef _H_GAMEMAP_H_
#define _H_GAMEMAP_H_
#include <string>
#include "MapCell.h"

using namespace std;
class GameMap
{
	typedef enum {
		Empty,
		Wall,
		Food,
		Vitamins
	} MapCells;

public:
	GameMap(size_t rows, size_t cols);
	~GameMap();

	bool load(string path);
	void setAt(GameObject* object, size_t x, size_t y);
	bool isAt(GameObject* object, size_t x, size_t y);

	MapCell* at(size_t x, size_t y){ return &board[x*_cols + y]; }

	size_t getRows() {return _rows;}
	size_t getCols() { return _cols; }
private:
	size_t _cols, _rows;
	MapCell* board = new MapCell[_rows * _cols];
};
#endif
