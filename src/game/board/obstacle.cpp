#include "obstacle.h"

Obstacle::Obstacle(unsigned int x, unsigned int y, int weight):
	Thing(x,y,weight)
	{}

std::ostream& Obstacle::print(std::ostream& out){
	out << "Obstacle" << std::endl;
	return out;
}

char Obstacle::to_char() {
	return 'O';
}
