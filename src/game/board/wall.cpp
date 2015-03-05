#include "wall.h"

Wall::Wall(unsigned int x, unsigned int y):
	Obstacle(x,y,false)
	{}

std::ostream& Wall::print(std::ostream& out){
	return out;
}
