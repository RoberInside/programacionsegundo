#ifndef _H_GHOST_H_
#define _H_GHOST_H_
#include "GameCharacter.h"
#include <stdlib.h>

#define thisGhostData pGame->getFileSystem()->getGhostsData()->ghosts[_id]

class Ghost: public GameCharacter
{
public:
	Ghost(Game* g, int id, int color);
	virtual ~Ghost();

	void update();
	void render();

	int getX() const { return posIniY; }
	int getY() const { return posIniX; }
	
	void kill();

	inline bool isKilleable() const { return killeable; };

	virtual void loadFromFile();
	virtual void saveToFile();

	bool isAlive() { return alive; }
protected:
	bool alive;
	int ss_col, ss_row;
	int _id;
	bool killeable;
	void move();
};

#endif