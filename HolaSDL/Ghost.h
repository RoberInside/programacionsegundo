#ifndef _H_GHOST_H_
#define _H_GHOST_H_
#include "GameCharacter.h"
#include <stdlib.h>

#define ghostsData pGame->getFileSystem()->getGhostsData()
#define thisGhostData pGame->getFileSystem()->getGhostsData()->ghosts[_id]

class Ghost: public GameCharacter
{
public:
	Ghost(Game* g, int id);
	virtual ~Ghost();

	void update();
	void render();

	int getX() const { return posIniY; }
	int getY() const { return posIniX; }
	
	void kill();

	virtual void loadFromFile();
	virtual void saveToFile();

	bool isAlive() { return alive; }
protected:
	bool alive;
	int ss_col, ss_row;
	int _id;
	
	void move();
};

#endif