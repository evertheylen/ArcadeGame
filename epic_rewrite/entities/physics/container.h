
#include "simplephysics.h"

#ifndef _H_Container
#define _H_Container

class Entity;  // forward declaration

// It seems that 
class Container: public SimplePhysics {
public:
	Container(int _height, int _weight);
	
	Entity* contained;
};

#endif
