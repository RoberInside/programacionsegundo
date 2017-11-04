#ifndef _H_GAMEOBJECT_H_
#define _H_GAMEOBJECT_H_
#include "Game.h"
#include "Texture.h"

using namespace std;
class GameObject {
public:
	enum ObjectType{
		Wall,
		Empty,
		Food,
		Vitamins,
		Ghost,
		Pacman
	};
private:
	Texture* texture = nullptr; // Puntero a su textura
	Game* game; // Puntero al juego al que pertenece
	size_t texRow, texCol; // Posición del frame en la textura

private:
	ObjectType _type;
protected:
	void setType(ObjectType type);

public:
	GameObject();
	~GameObject();
	void render();
	void update();
	ObjectType getType();
};

#endif