
#include "physics.h"

#ifndef _H_SimplePhysics
#define _H_SimplePhysics

class SimplePhysics: public virtual Physics {
public:
	
	SimplePhysics(int _height, int _weight, unsigned int _x, unsigned int _y);
	
	int get_height();
	int get_weight();

	unsigned int get_x();
	unsigned int get_y();

private:
	int height;
	int weight;
	unsigned int x;
	unsigned int y;
};

#endif
