#include "wall.h"

Wall::Wall(unsigned int x, unsigned int y):
	Obstacle(x,y,-1)  // inf weight
	{
	_initCheck = this;
}

std::ostream& Wall::print(std::ostream& out){
	return out;
}

char Wall::to_char() {
	return 'X';
}
