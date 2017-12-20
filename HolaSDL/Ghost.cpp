#include "Ghost.h"
#include "Game.h"

Ghost::Ghost(Game* g, int id)
{
	pGame = g;
	loadFromFile();
	//ss_col = color * 2;
	ss_row = 0;

	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	pGame->rectToTile(_rect);
	_rect.x = posIniX * _rect.w;
	_rect.y = posIniY * _rect.h;
	text = pGame->getTexture(Game::Texture_t::tPjes);
	
	alive = true;
}


Ghost::~Ghost()
{
	delete text;
	text = nullptr;
}

void Ghost::update()
{
	if (alive) {
		move();
	}
}

void Ghost::render()
{

	if (ss_col % 2 == 0) ss_col++;
	else ss_col--;

	text->renderFrame(pGame->getRenderer(), _rect, ss_row, ss_col, SDL_FLIP_NONE);
	
}

void Ghost::kill()//Provisional
{
	alive = false;
}

void Ghost::loadFromFile()
{
	posActX = thisGhostData.pos.x;
	posActY = thisGhostData.pos.y;

	posIniX = thisGhostData.posini.x;
	posIniY = thisGhostData.posini.y;

	dirX = thisGhostData.dir.x;
	dirY = thisGhostData.dir.y;
}

void Ghost::saveToFile()
{
	thisGhostData.pos.x = posActX;
	thisGhostData.pos.y = posActY;

	thisGhostData.posini.x = posIniX;
	thisGhostData.posini.y = posIniY;

	thisGhostData.dir.x = dirX;
	thisGhostData.dir.y = dirY;
}

void Ghost::move()
{
	int nx = posIniX;
	int ny = posIniY;	
	int randomDir = rand() % 4;

	switch (randomDir)
	{
	case 0: //arriba
		ny--;
		break;
	case 1: //abajo
		ny++;
		break;
	case 2: //dcha
		nx++;
		break;
	case 3: //izda
		nx--;
		break;
	default:
		break;
	}
	if (pGame->canMoveTo(ny, nx)) {
		posIniX = nx;
		posIniY = ny;

		ss_row = randomDir;
		_rect.x = posIniX * _rect.w;
		_rect.y = posIniY * _rect.h;

	}
	else { // esta modificacion la he depurado y responde bien pero apenas se nota ya que
		//sigue siendo aleatorio y no se me ocurria otra cosa de momento falta poner que
		//no se superpongan los fantasmas en el canMoveTo pero no se me ocurria como
		if (nx > posIniX && pGame->canMoveTo(ny, nx - 2)) { // si no puede a la dcha, se mueve a
													 // la izda si esta disponible
			posIniX = nx - 2;
			ss_row = randomDir;
		}
		else if (nx < posIniX && pGame->canMoveTo(ny, nx + 2)) {// si no puede a la izda, 
												// se mueve a la dcha si esta disponible
			posIniX = nx + 2;
			ss_row = randomDir;
		}
		if (ny > posIniY && pGame->canMoveTo(ny - 2, nx)) {// si no puede abajo, se mueve arriba 
												   // si esta disponible
			posIniY = ny - 2;
			ss_row = randomDir;
		}
		else if (ny < posIniY && pGame->canMoveTo(ny + 2, nx)) {// si no puede arriba, se mueve
														// abajo si esta disponible
			posIniY = ny + 2;
			ss_row = randomDir;
		}
		
		_rect.x = posIniX * _rect.w;
		_rect.y = posIniY * _rect.h;

	}

}

