#ifndef _H_PACMAN_H_
#define _H_PACMAN_H_
#include "GameCharacter.h"

const int superModeTime = 5 * 1000;//ms


class Pacman: public GameCharacter
{
public:
	Pacman(Game* g,int x, int y);
	virtual ~Pacman();

	void update();
	void render();

	int getX() const { return posIniY; }
	int getY() const { return posIniX; }

	void setSuperMode() { superMode = true; };
	bool isSuperMode() { return superMode; }
private:
	int ss_col, ss_row;

	bool superMode;
	
	void move();
	


};

#endif