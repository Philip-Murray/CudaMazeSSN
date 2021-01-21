#pragma once
#include <string>

class Position {
	int x;
	int y;

public:
	Position(const int posx, const int posy) :
		x(posx), y(posy) {
	}
	

	bool operator==(const Position& other) const {
		return getX() == other.getX() && getY() == other.getY();
	}
	bool operator!=(const Position& other) const {
		return getX() != other.getX() || getY() != other.getY();
	}

	Position plus(int x, int y) const {
		return Position(getX() + x, getY() + y);
	}
	void increment(int x, int y) {
		this->x += x; this->y += y;
	}

	int getX() const { return x;}
	int getY() const { return y;}
	
	Position() { x = 0; y = 0; };


	std::string getString() {
		return "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
	}

};
