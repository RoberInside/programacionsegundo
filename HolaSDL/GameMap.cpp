#include "GameMap.h"
#include "Game.h"

GameMap::GameMap(Game* game)
{
	pGame = game;

	_rows = pGame->getFileSystem()->getMapData()->rows;
	_cols = pGame->getFileSystem()->getMapData()->cols;


	//INIT BOARD/////////
	board = new MapCell_t*[_rows];

	for (size_t i = 0; i < _rows; i++)
	{
		board[i] = new MapCell_t[_cols];
	}
	//FORMAT TILE
	rect.x = rect.y = rect.w = rect.h = 0;
	pGame->rectToTile(rect);

	//GET TEXTURES////////////
	wallText	= pGame->getTexture(Game::Texture_t::tWall);

	vitiminText = pGame->getTexture(Game::Texture_t::tVitamin);

	foodText	= pGame->getTexture(Game::Texture_t::tFood);

	emptyText	= pGame->getTexture(Game::Texture_t::tPjes);

	fontText = pGame->getTexture(Game::Texture_t::tFont);

	loadFromFile();
}


GameMap::~GameMap()
{
	if (board != nullptr) {
		for (size_t i = 0; i < _rows; i++)
		{
			delete[] board[i];
		}
		delete[] board;
	}
	board = nullptr;
}

void GameMap::loadFromFile() {
	for (int i = 0; i < _rows; i++) {
		for (size_t j = 0; j < _cols; j++)
		{
			board[i][j] = (MapCell_t)pGame->getFileSystem()->getMapData()->map[i*_cols + j];
		}
	}
}

void GameMap::saveToFile() {
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _cols; j++)
		{
			pGame->getFileSystem()->getMapData()->map[i*_cols + j] = board[i][j];
		}
	}
}
void GameMap::setAt(MapCell_t type, size_t x, size_t y)
{
	if (isInside(x, y))
		board[x][y] = type;
}

bool GameMap::isAt(MapCell_t type, size_t y, size_t x)const
{
	return (isInside(x, y) && board[x][y] == type);
}

bool GameMap::isEmpty(size_t x, size_t y)const
{
	return (isInside(x, y) && (board[x][y] == MapCell_t::Empty || 
		board[x][y] != MapCell_t::Wall));
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
	fontText->loadFromText(pGame->getRenderer(), "Puntos " + to_string(pGame->getScore()), pGame->getColor());
	fontText->render(pGame->getRenderer(), &fontText->font.setRect(50, 200, 10, 560));
}
bool GameMap::isInside(int x, int y) const
{
	return (x >= 0 && y >= 0 && y <(int)_cols && x < (int)_rows);
}

