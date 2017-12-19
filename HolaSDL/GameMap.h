#ifndef _H_GAMEMAP_H_
#define _H_GAMEMAP_H_

#include "GameObject.h"

using namespace std;
enum class MapCell_t {
	Empty,
	Wall,
	Food,
	Vitamins
};

class GameMap: public GameObject
{
	friend class Game;	
	
public:
	GameMap(Game* game, size_t rows, size_t cols);
	virtual ~GameMap();

	void setAt(MapCell_t type, size_t x, size_t y);
	bool isAt(MapCell_t type, size_t x, size_t y) const;
	bool isEmpty(size_t x, size_t y) const;

	size_t getRows()const { return _rows; }
	size_t getCols()const { return _cols; }

	void render();

	virtual void update() {}
	virtual void loadFromFile();
	virtual void saveToFile();

private:
	bool isInside(int x, int y)const;
	size_t _cols, _rows;
	MapCell_t** board;

	bool* visited;
	

	SDL_Rect rect;

	Texture* wallText;
	Texture* emptyText;
	Texture* vitiminText;
	Texture* foodText;

};
#endif
