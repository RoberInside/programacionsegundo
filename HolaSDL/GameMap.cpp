#include "GameMap.h"
#include "Game.h"


GameMap::GameMap(Game* game, size_t rows, size_t cols):pGame(game), _rows(rows), _cols(cols)
{
	board = new MapCell_t*[rows +2];
	for (size_t i = 0; i < rows; i++)
	{
		board[i] = new MapCell_t[cols];
	}
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);

	wallText = new Texture();
	wallText->load(pGame->getRenderer(), pGame->getTextPath(Game::tWall));
	
	vitiminText = new Texture();
	vitiminText->load(pGame->getRenderer(), pGame->getTextPath(Game::tVitamin));

	foodText = new Texture();
	foodText->load(pGame->getRenderer(), pGame->getTextPath(Game::tFood));
	
	emptyText = new Texture();
	emptyText->load(pGame->getRenderer(), pGame->getTextPath(Game::tEmpty));

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
	return (isInside(x, y) && board[x][y] == MapCell_t::Empty);
}

void GameMap::render()
{
	//SDL_Rect rect;
	pGame->rectToTile(rect);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols ; j++)
		{
			rect.x = i * rect.w;
			rect.y = j * rect.h;
			switch (board[i][j])
			{
			case MapCell_t::Wall:
				wallText->render(pGame->getRenderer(), &rect);
				break;
			case MapCell_t::Empty:
				emptyText->render(pGame->getRenderer(), &rect);
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

bool GameMap::isInside(int y, int x)// estaba mal planteado
{
	return (x >= 0 && y >= 0 && x <(int)_cols && y < (int)_rows);
}

