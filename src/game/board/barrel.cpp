#include "barrel.h"

Barrel::Barrel(unsigned int x, unsigned int y):
	Obstacle(x,y,1000)
	{}

std::ostream& Barrel::print(std::ostream& out){
	out << "Er bevindt zich een ton op positie ";
	return out;
}

char Barrel::to_char() {
	return '#';
}
