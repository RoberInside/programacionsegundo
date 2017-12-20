#ifndef _H_GAMEMAP_H_
#define _H_GAMEMAP_H_

#include "GameObject.h"

using namespace std;
enum MapCell_t {
	Empty = 0,
	Wall = 1,
	Vitamins = 2,
	Food = 3
};

class GameMap: public GameObject
{
	friend class Game;	
	
public:
	GameMap(Game* game);
	virtual ~GameMap();

	void setAt(MapCell_t type, size_t x, size_t y);
	bool isAt(MapCell_t type, size_t x, size_t y) const;
	bool isEmpty(size_t x, size_t y) const;

	size_t getRows()const { return _rows; }
	size_t getCols()const { return _cols; }

	void render();

	void update() {};
	void loadFromFile();
	void saveToFile();

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
