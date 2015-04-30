
#include "ia/ia.h"
#include "life/life.h"
#include "physics/physics.h"
#include "printer/printer.h"

#ifndef _H_Entity
#define _H_Entity

// If you don't like multiple inheritance, you should stop reading right now and find some other
// project you like. I'm serious. Also, if you don't like virtuals or RTTI in general, consider
// rm -rf'ing your local copy of this project, and then watching some cat gifs.

// If you _do_ like MI and RTTI, buckle up, this is going to be quite a ride.

class Entity: public virtual Interactive, public virtual Life, public virtual Physics, public virtual Printer {
public:
	virtual void __polymorphic__() {}
	
	Entity(unsigned int _x, unsigned int _y);
	
	virtual ~Entity() {}
	
	// x and y can be both getted and setted, so it's better to make them public anyways.
	unsigned int x;
	unsigned int y;
};

#endif
