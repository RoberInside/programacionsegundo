#ifndef _H_CHARACTER_H_
#define _H_CHARACTER_H_
#include "GameObject.h"

//Constants
const GameObject::Position UP = { 0, 1 };
const GameObject::Position DOWN = { 0, -1 };
const GameObject::Position RIGHT = { 1, 0 };
const GameObject::Position LEFT = { -1, 0 };

enum class Direction { UP, DOWN, RIGHT, LEFT };

class Character:
	public GameObject
{
public:
	Character();
	virtual ~Character() {};

	void update();
	void draw();
protected:
	void move(Direction dir);
	virtual Position controller() = 0;
private:
	bool collision(Position target);

};

#endif 