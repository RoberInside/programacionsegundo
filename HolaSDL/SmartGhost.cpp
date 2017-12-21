#include "SmartGhost.h"
#include "Game.h"

SmartGhost::SmartGhost(Game* g, int id): Ghost(g, id, 4/*We know they will always have this sprite*/)
{
}

SmartGhost::~SmartGhost()
{
}

void SmartGhost::update()
{
}

void SmartGhost::loadFromFile()
{
	Ghost::loadFromFile();
	age = pGame->getFileSystem()->getGhostsData()->ghosts[_id].age;
}

void SmartGhost::saveToFile()
{
	Ghost::saveToFile();
	pGame->getFileSystem()->getGhostsData()->ghosts[_id].age = age;
}
