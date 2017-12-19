#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(Game* g, int x, int y)
{
	pGame = g;
	posIniX = y;
	posIniY = x;
	ss_col = 10;
	ss_row = 0;

	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	
	pGame->rectToTile(_rect);
	_rect.x = posIniX * _rect.w;
	_rect.y = posIniY * _rect.h;
	text = pGame->getTexture(Game::Texture_t::tPjes);

	superMode = false;
}

Pacman::~Pacman()
{
	delete pGame;
	pGame = nullptr;

	delete text;
	text = nullptr;
}

void Pacman::update()
{
	move();
}

void Pacman::render()
{	

	if (ss_col % 2 == 0)ss_col++;
	else ss_col--;

	text->renderFrame(pGame->getRenderer(), _rect, ss_row, ss_col, SDL_FLIP_NONE);
}

void Pacman::move()
{
	int nx = posIniX;
	int ny = posIniY;
	
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
		posIniX = nx;
		posIniY = ny;

		_rect.x = posIniX * _rect.w;
		_rect.y = posIniY * _rect.h;
		
		ss_row = (int)pGame->getNextDir();

	}
}
