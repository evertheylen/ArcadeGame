
#include "physics.h"

#ifndef _H_SimplePhysics
#define _H_SimplePhysics

class SimplePhysics: public virtual Physics {
public:
	
	SimplePhysics(int _height, int _weight);
	
	int get_height();
	int get_weight();

private:
	int height;
	int weight;
};

#endif
