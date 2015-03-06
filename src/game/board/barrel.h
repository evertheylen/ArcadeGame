#include "obstacle.h"

#ifndef _Barrel
#define _Barrel

class Barrel: public Obstacle {
public:
	Barrel(unsigned int x, unsigned int y);
	std::ostream& print(std::ostream& out);
	
	char to_char();
};


#endif // _Barrel
