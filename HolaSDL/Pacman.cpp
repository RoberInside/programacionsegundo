#include "Pacman.h"
#include "Game.h" //evitar recursion ciclica


Pacman::Pacman(Game* g)
{
	pGame = g;
	loadFromFile();

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

bool Pacman::kill()
{
	lifes--;
	return lifes <= 0;
}
void Pacman::loadFromFile() {
	posIniX = pGame->getFileSystem()->getPacmanData()->posini.x;
	posIniY = pGame->getFileSystem()->getPacmanData()->posini.y;

	posActX = pGame->getFileSystem()->getPacmanData()->pos.x;
	posActY = pGame->getFileSystem()->getPacmanData()->pos.y;

	dirX = pGame->getFileSystem()->getPacmanData()->dir.x;
	dirY = pGame->getFileSystem()->getPacmanData()->dir.y;

	lifes = pGame->getFileSystem()->getPacmanData()->lifes;

	energy = pGame->getFileSystem()->getPacmanData()->energy;
}
void Pacman::saveToFile() {
	pGame->getFileSystem()->getPacmanData()->posini.x = posIniX;
	pGame->getFileSystem()->getPacmanData()->posini.y = posIniY;

	pGame->getFileSystem()->getPacmanData()->pos.x = posActX;
	pGame->getFileSystem()->getPacmanData()->pos.y = posActY;

	pGame->getFileSystem()->getPacmanData()->dir.x = dirX;
	pGame->getFileSystem()->getPacmanData()->dir.y = dirY;

	pGame->getFileSystem()->getPacmanData()->lifes = lifes;

	pGame->getFileSystem()->getPacmanData()->energy = energy;
}