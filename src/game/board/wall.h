#include "obstacle.h"

#ifndef _Wall
#define _Wall

class Wall: public Obstacle {
public:
	Wall(unsigned int x, unsigned int y);
	std::ostream& print(std::ostream& out);
	
	char to_char();
};


#endif // _Wall
