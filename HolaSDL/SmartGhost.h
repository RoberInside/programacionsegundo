#pragma once
#include "Ghost.h"
class SmartGhost : public Ghost
{
public:
	SmartGhost(Game* g, int id) ;
	virtual ~SmartGhost();

	void update();
	void loadFromFile();
	void saveToFile();

private:
	size_t age;
};

