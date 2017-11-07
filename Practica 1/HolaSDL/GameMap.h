#ifndef _H_GAMEMAP_H_
#define _H_GAMEMAP_H_
#include <string>
#include "Position.h"

using namespace std;
enum MapCell_t {
	Empty,
	Wall,
	Foods,
	Vitamins
};

class GameMap
{
	
public:
	GameMap(size_t rows, size_t cols);
	~GameMap();

	void setAt(MapCell_t type, size_t x, size_t y);
	bool isAt(MapCell_t type, size_t x, size_t y);
	bool isEmpty(size_t x, size_t y);
	bool isEmpty(Position pos);

	size_t getRows() { return _rows;}
	size_t getCols() { return _cols; }
private:
	size_t _cols, _rows;
	vector<vector<MapCell_t>> board;
};
#endif
