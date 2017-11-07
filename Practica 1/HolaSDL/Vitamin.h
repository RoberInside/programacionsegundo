#ifndef _H_VITAMIN_H_
#define _H_VITAMIN_H_
#include "GameObject.h"
class Vitamin :
	public GameObject
{
public:
	Vitamin(int x, int y);
	Vitamin(Position pos);
	~Vitamin();
	void update();
	void render();
};
#endif // !_H_VITAMIN_H_


