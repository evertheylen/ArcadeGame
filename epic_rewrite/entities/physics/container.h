
#include "simplephysics.h"

#ifndef _Container
#define _Container

class Entity;  // forward declaration

class Container: public SimplePhysics {
public:
	Container(int _height, int _weight);
	
	Entity* contained;
};

#endif
