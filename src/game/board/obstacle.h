#include "thing.h"
#include <string>

#ifndef _Obstacle
#define _Obstacle

class Obstacle: public Thing {
public:
	Obstacle(unsigned int x, unsigned int y, bool movable);
};

#endif // _Obstacle
