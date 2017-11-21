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
	
	move();
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

void Ghost::move()
{
	int nx = _x;
	int ny = _y;	
	int random = rand() % 4;

	switch (random)
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
		_x = nx;
		_y = ny;

		_rect.x = _x * _rect.w;
		_rect.y = _y * _rect.h;

	}
	else { // esta modificacion la he depurado y responde bien pero apenas se nota ya que
		//sigue siendo aleatorio y no se me ocurria otra cosa de momento falta poner que
		//no se superpongan los fantasmas en el canMoveTo pero no se me ocurria como
		if (nx > _x && pGame->canMoveTo(ny, nx - 2)) // si no puede a la dcha, se mueve a
												     // la izda si esta disponible
			_x = nx - 2;
		else if (nx < _x && pGame->canMoveTo(ny, nx + 2))// si no puede a la izda, 
												// se mueve a la dcha si esta disponible
			_x = nx + 2;
		if(ny > _y && pGame->canMoveTo(ny - 2, nx))// si no puede abajo, se mueve arriba 
												   // si esta disponible
			_y = ny - 2;
		else if(ny < _y && pGame->canMoveTo(ny + 2, nx))// si no puede arriba, se mueve
														// abajo si esta disponible
		_y = ny + 2;

		_rect.x = _x * _rect.w;
		_rect.y = _y * _rect.h;

	}

}
