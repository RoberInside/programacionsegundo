#ifndef _H_GHOST_H_
#define _H_GHOST_H_
#include "GameCharacter.h"
#include <stdlib.h>

class Ghost: public GameCharacter
{
public:
	Ghost(Game* g, int x, int y, int color);
	virtual ~Ghost();

	void update();
	void render();

	int getX() const { return posIniY; }
	int getY() const { return posIniX; }
	
	void kill();

	bool isAlive() { return alive; }
private:
	bool alive;
	int ss_col, ss_row;
		
	
	void move();
};

#endif