#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(Game* g, int x, int y):pGame(g)
{
	_x = x;
	_y = y;
	
	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	g->rectToTile(_rect);
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	texture = new Texture();
	texture->load(pGame->getRenderer() , "..\\images\\pacman.png");
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
	SDL_Rect rect;
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);
	rect.x = _x * rect.w;
	rect.y = _y * rect.h;
	texture->render(pGame->getRenderer(), &rect);
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
		ny--;
		break;
	default:
		break;
	}
	if (pGame->canMoveTo(nx, ny)) {
		_x = nx;
		_y = ny;
		updateRect();
	}
}

void Pacman::updateRect()
{
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
}


