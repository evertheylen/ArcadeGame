#include "obstacle.h"

Obstacle::Obstacle(unsigned int x, unsigned int y, bool movable):
	Thing(x,y,movable)
	{}

std::ostream& Obstacle::print(std::ostream& out){
	out << "Obstacle" << std::endl;
	return out;
}

char Obstacle::to_char() {
	return 'O';
}
