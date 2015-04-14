
#include "physics.h"

#ifndef _SimplePhysics
#define _SimplePhysics

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
