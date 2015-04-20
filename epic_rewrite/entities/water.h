
#include "entity.h"

#include "life/immutable.h"
#include "physics/simplephysics.h"
#include "printer/simpleprint.h"
#include "ia/lethal.h"

#ifndef _H_Water
#define _H_Water

class Water: public Lethal, public Immutable, public SimplePhysics, public SimplePrint, public Entity {
public:
	Water();

	Entity* contained;	//TODO Make a printer based on what is in contained.
};

#endif
