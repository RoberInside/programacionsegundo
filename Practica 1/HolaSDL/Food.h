#ifndef _H_FOOD_H_
#define _H_FOOD_H_
#include "GameObject.h"
class Food :
	public GameObject
{
public:
	Food(int x, int y);
	Food(Position pos);
	~Food();
	void render();
	void update();
};

#endif