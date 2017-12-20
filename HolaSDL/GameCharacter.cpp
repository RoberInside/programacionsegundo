#include "GameCharacter.h"
#include "Game.h"


GameCharacter::GameCharacter()
{
}


GameCharacter::~GameCharacter()
{
	
}

void GameCharacter::render()
{
	SDL_Rect rect;
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);
	rect.x = posIniX * rect.w;
	rect.y = posIniY * rect.h;
}