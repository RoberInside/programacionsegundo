#ifndef POSITION
#define POSITION
class Position
{
public:
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
#endif // !POSITION


