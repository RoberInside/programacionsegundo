#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(Game* g, int x, int y):pGame(g)
{
	_x = x;
	_y = y;
	_row = 0;
	_col = 10;
	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	pGame->rectToTile(_rect);
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	texture = pGame->getTexture(Game::Texture_t::tPjes);
}

Pacman::~Pacman()
{
	delete texture;
}

void Pacman::update()
{

	move();
}

void Pacman::render()
{
	if (_col % 2 == 0) _col++;
	else _col--;
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	texture->renderFrame(pGame->getRenderer(), _rect, _row, _col, SDL_FLIP_NONE);
}

void Pacman::move()
{
	int nx = _x;
	int ny = _y;
	switch (pGame->getNextDir())
	{
	case Game::Direction::UP:
		_row = 3;
		ny--;
		break;
	case Game::Direction::DOWN:
		_row = 1;
		ny++;
		break;
	case Game::Direction::RIGHT:
		_row = 0;
		nx++;
		break;
	case Game::Direction::LEFT:
		_row = 2;
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


