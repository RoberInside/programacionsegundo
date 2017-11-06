#ifndef _H_CHARACTER_H_
#define _H_CHARACTER_H_
#include "GameObject.h"

class Character:
	public GameObject
{
public:
	Character(int x, int y);
	virtual ~Character() {};

	void update();
	void draw();
protected:
	void move(Position pos);
	virtual Position controller() = 0;
private:
	bool collision(Position target);

};

#endif 