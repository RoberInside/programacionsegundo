#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(Game* g, int x, int y):pGame(g)
{
	_x = x;
	_y = y;
	
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

	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	texture->renderFrame(pGame->getRenderer(), _rect, 0, 10, SDL_FLIP_NONE);
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
	if (pGame->canMoveTo(nx, ny)) {
		_x = nx;
		_y = ny;

		_rect.x = _x * _rect.w;
		_rect.y = _y * _rect.h;
	}
}


