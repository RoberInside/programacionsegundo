#include "Ghost.h"
#include "Game.h"

Ghost::Ghost(Game* g, int x, int y):pGame(g)
{
	_x = y;
	_y = x;

	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	pGame->rectToTile(_rect);
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	gText = pGame->getTexture(Game::Texture_t::tPjes);
	
}


Ghost::~Ghost()
{
	delete gText;
}

void Ghost::update()
{
	int random = rand()%4;
	move(random);
}

void Ghost::render(int g)
{
	
	SDL_Rect rect;
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);
	rect.x = _x * rect.w;
	rect.y = _y * rect.h;

	g = g * 2;
	gText->renderFrame(pGame->getRenderer(), rect, 0, g, SDL_FLIP_NONE);
	
	
}

void Ghost::move(int m)
{
	int nx = _x;
	int ny = _y;	


	switch (m)
	{
	case 0:
		ny--;
		break;
	case 1:
		ny++;
		break;
	case 2:
		nx++;
		break;
	case 3:
		nx--;
		break;
	default:
		break;
	}
	if (pGame->canMoveTo(ny, nx)) {
		_x = nx;
		_y = ny;

		_rect.x = _x * _rect.w;
		_rect.y = _y * _rect.h;

	}

}
