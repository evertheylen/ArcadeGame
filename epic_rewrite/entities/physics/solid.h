
#include "physics.h"

#ifndef _H_Solid
#define _H_Solid

class Solid: public virtual Physics {
public:
	
	SimplePhysics(int _height, int _weight);
	
	int get_height();
	int get_weight();

private:
	int height;
	int weight;
};

#endif
