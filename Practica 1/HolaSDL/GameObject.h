#ifndef _H_GAMEOBJECT_H_
#define _H_GAMEOBJECT_H_
#include "Game.h"
#include "Texture.h"
#include "GameMap.h"
#include "Position.h"

using namespace std;
/*Estructura auxiliar para posiciones*/

/*Clase abstracta que sirve como padre de todos los objetos del juego*/
class GameObject {

public:
	GameObject() { pGame->rectToTile(rect); };
	virtual ~GameObject() {};

	enum class ObjectType{
		Wall,
		Empty,
		Food,
		Vitamins,
		Ghost,
		Pacman
	};
protected:
	Position pos;
	SDL_Rect rect;
	Texture* pTexture;
	Game* pGame;
	size_t texRow, texCol; // Posición del frame en la textura
	ObjectType _type;
public:
	void render();
	virtual void update() = 0;
	ObjectType getType() { return _type; };
	Position getPosition() { return pos; };
};

#endif