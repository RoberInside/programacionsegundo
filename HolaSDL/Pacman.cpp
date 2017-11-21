#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(Game* g, int x, int y):pGame(g)
{
	_x = y;
	_y = x;
	ss_col = 10;
	ss_row = 0;

	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	pGame->rectToTile(_rect);
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	pacText = pGame->getTexture(Game::Texture_t::tPjes);
	
}

Pacman::~Pacman()
{
	delete pacText;
}

void Pacman::update()
{
	
	move();
}

void Pacman::render()
{
	SDL_Rect rect;
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);
	rect.x = _x * rect.w;
	rect.y = _y * rect.h;

	if (ss_col % 2 == 0)ss_col++;
	else ss_col--;

	pacText->renderFrame(pGame->getRenderer(), rect, ss_row, ss_col, SDL_FLIP_NONE);
}

void Pacman::move()
{
	int nx = _x;
	int ny = _y;
	
	switch (pGame->getNextDir())
	{
	case Game::Direction::UP:
		ny--;
		break;
	case Game::Direction::DOWN:
		ny++;
		break;
	case Game::Direction::RIGHT:
		nx++;
		break;
	case Game::Direction::LEFT:
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
		
		ss_row = (int)pGame->getNextDir();

	}
}
