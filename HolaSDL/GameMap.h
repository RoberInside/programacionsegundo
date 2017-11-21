#ifndef _H_GAMEMAP_H_
#define _H_GAMEMAP_H_
#include "Texture.h"

#include <string>
#include <vector>
class Game;
using namespace std;
enum class MapCell_t {
	Empty,
	Wall,
	Food,
	Vitamins
};

class GameMap
{
	friend class Game;	
	
public:
	GameMap(Game* game, size_t rows, size_t cols);
	~GameMap();

	void setAt(MapCell_t type, size_t x, size_t y);
	bool isAt(MapCell_t type, size_t x, size_t y);
	bool isEmpty(size_t x, size_t y);

	size_t getRows() { return _rows; }
	size_t getCols() { return _cols; }

	void render();
	bool isInside(int x, int y);
private:
	size_t _cols, _rows;
	MapCell_t** board;

	Game* pGame;

	SDL_Rect rect;

	Texture* wallText;
	Texture* emptyText;
	Texture* vitiminText;
	Texture* foodText;

};
#endif
