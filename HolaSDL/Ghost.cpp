#include "Ghost.h"
#include "Game.h"

Ghost::Ghost(Game* g, int x, int y, int color):pGame(g)
{
	_x = y;
	_y = x;
	this->color = color;
	ss_col = color * 2;
	ss_row = 0;

	_rect.x = _rect.y = _rect.w = _rect.h = 0;
	pGame->rectToTile(_rect);
	_rect.x = _x * _rect.w;
	_rect.y = _y * _rect.h;
	gText = pGame->getTexture(Game::Texture_t::tPjes);
	
	alive = true;
}


Ghost::~Ghost()
{
	delete gText;
}

void Ghost::update()
{
	pGame->isSuperMode() ? ss_col = 7 * 2 : color * 2;
	if (alive) {
		move();
	}
}

void Ghost::render()
{
	SDL_Rect rect;

	if (supermode) {
		if (alive) {
			//ss_row % 4 ? ss_row = 0 : ;
		}
		else {
			ss_row = 2;
		}
	}

	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);
	rect.x = _x * rect.w;
	rect.y = _y * rect.h;

	ss_col % 2 ? ss_col++ : ss_col--;

	gText->renderFrame(pGame->getRenderer(), rect, ss_row, ss_col, SDL_FLIP_NONE);
}

void Ghost::kill()//Provisional
{
	alive = false;
}

void Ghost::move()
{
	int nx = _x;
	int ny = _y;	
	int randomDir = rand() % 4;

	switch (randomDir)
	{
	case 3: //arriba
		ny--;
		break;
	case 1: //abajo
		ny++;
		break;
	case 0: //dcha
		nx++;
		break;
	case 2: //izda
		nx--;
		break;
	default:
		break;
	}
	if (pGame->canMoveTo(ny, nx)) {
		_x = nx;
		_y = ny;

		ss_row = randomDir;
		_rect.x = _x * _rect.w;
		_rect.y = _y * _rect.h;

	}
	else { // esta modificacion la he depurado y responde bien pero apenas se nota ya que
		//sigue siendo aleatorio y no se me ocurria otra cosa de momento falta poner que
		//no se superpongan los fantasmas en el canMoveTo pero no se me ocurria como
		if (nx > _x && pGame->canMoveTo(ny, nx - 2)) { // si no puede a la dcha, se mueve a
													 // la izda si esta disponible
			_x = nx - 2;
			ss_row = randomDir;
		}
		else if (nx < _x && pGame->canMoveTo(ny, nx + 2)) {// si no puede a la izda, 
												// se mueve a la dcha si esta disponible
			_x = nx + 2;
			ss_row = randomDir;
		}
		if (ny > _y && pGame->canMoveTo(ny - 2, nx)) {// si no puede abajo, se mueve arriba 
												   // si esta disponible
			_y = ny - 2;
			ss_row = randomDir;
		}
		else if (ny < _y && pGame->canMoveTo(ny + 2, nx)) {// si no puede arriba, se mueve
														// abajo si esta disponible
			_y = ny + 2;
			ss_row = randomDir;
		}

		_rect.x = _x * _rect.w;
		_rect.y = _y * _rect.h;

	}

}
