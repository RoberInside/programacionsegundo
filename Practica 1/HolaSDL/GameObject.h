#ifndef _H_GAMEOBJECT_H_
#define _H_GAMEOBJECT_H_
#include "Game.h"
#include "Texture.h"
#include "GameMap.h"

using namespace std;
/*Clase abstracta que sirve como padre de todos los objetos del juego*/
class GameObject {
	/*Estructura auxiliar para posiciones*/
public:
	struct Position{
		int x;
		int y;
		Position() { this->x = 0; this->y = 0; };
		Position(int x, int y) { this->x = x; this->y = y; };

		Position* operator+=(Position other) {
			this->x += other.x;
			this->y += other.y;
			return this;
		}
		Position* operator*=(int scalar) {
			this->x *= scalar;
			this->y *= scalar;
			return this;
		}
		Position* operator=(Position other) {
			this->x = other.x;
			this->y = other.y;
			return this;
		}
		bool operator== (Position other) {
			return (this->x == other.x) && (this->y == other.y);
		}
		bool operator!= (Position other) {
			return !(*(this) == other);
		}

	};
public:
	GameObject() {};
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
	Texture* texture; // Puntero a su textura
	Game* game; // Puntero al juego al que pertenece
	size_t texRow, texCol; // Posición del frame en la textura
	ObjectType _type;
public:
	~GameObject();
	virtual void render() {} = 0;
	virtual void update() {} = 0;
	ObjectType getType() { return _type; };
};

#endif