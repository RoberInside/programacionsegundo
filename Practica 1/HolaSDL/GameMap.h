#ifndef _H_GAMEMAP_H_
#define _H_GAMEMAP_H_
#include <string>
#include "GameObject.h"

using namespace std;
class GameMap
{
	enum MapCell_t {
		Empty,
		Wall,
		Food,
		Vitamins
	};
	struct MapCell
	{
		MapCell_t type;
		GameObject * obj;
	};
public:
	GameMap(size_t rows, size_t cols);
	~GameMap();

	void setAt(GameObject* object, size_t x, size_t y);
	bool isAt(GameObject::ObjectType type, size_t x, size_t y);
	bool isEmpty(size_t x, size_t y);

	MapCell* at(size_t x, size_t y){ return &board[x*_cols + y]; }

	size_t getRows() {return _rows;}
	size_t getCols() { return _cols; }
private:
	size_t _cols, _rows;
	MapCell* board = new MapCell[_rows * _cols];
};
#endif
