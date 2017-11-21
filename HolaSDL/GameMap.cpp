#include "GameMap.h"
#include "Game.h"


GameMap::GameMap(Game* game, size_t rows, size_t cols) :pGame(game), _rows(rows), _cols(cols)
{
	//INIT BOARD/////////
	board = new MapCell_t*[rows];

	for (size_t i = 0; i < rows; i++)
	{
		board[i] = new MapCell_t[cols];
	}
	//FORMAT TILE
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);

	//GET TEXTURES////////////
	wallText	= pGame->getTexture(Game::Texture_t::tWall);

	vitiminText = pGame->getTexture(Game::Texture_t::tVitamin);

	foodText	= pGame->getTexture(Game::Texture_t::tFood);

	emptyText	= pGame->getTexture(Game::Texture_t::tPjes);
}


GameMap::~GameMap()
{
	if (board != nullptr) {
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _cols; j++)
			{
				delete[] board[i];
			}
			delete board[i];
		}
	}
	board = nullptr;
}

void GameMap::setAt(MapCell_t type, size_t x, size_t y)
{
	if (isInside(x, y))
		board[x][y] = type;
}

bool GameMap::isAt(MapCell_t type, size_t x, size_t y)
{
	return (isInside(x, y) && board[x][y] == type);
}

bool GameMap::isEmpty(size_t x, size_t y)
{
	return (isInside(x, y) && (board[x][y] == MapCell_t::Empty || 
		board[x][y] == MapCell_t::Vitamins|| board[x][y] == MapCell_t::Food));
}

void GameMap::render()
{

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			rect.y = i * rect.h; 
			rect.x = j * rect.w;
			switch (board[i][j])
			{
			case MapCell_t::Wall:
				wallText->render(pGame->getRenderer(), &rect);
				break;
			case MapCell_t::Empty:
				emptyText->renderFrame(pGame->getRenderer(), rect, 3, 13, SDL_FLIP_NONE);
				break;
			case MapCell_t::Vitamins:
				vitiminText->render(pGame->getRenderer(), &rect);
				break;
			case MapCell_t::Food:
				foodText->render(pGame->getRenderer(), &rect);
				break;
			default:
				break;
			}

		}
	}
}

bool GameMap::isInside(int x, int y)// estaba mal planteado
{
	return (x >= 0 && y >= 0 && y <(int)_cols && x < (int)_rows);
}

