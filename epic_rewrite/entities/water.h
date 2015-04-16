
#include "entity.h"

#include "life/immutable.h"
#include "physics/container.h"
#include "printer/simpleprint.h"
#include "ia/lethal.h"

#ifndef _H_Water
#define _H_Water

class Water: public Immutable, public Container, public SimplePrint, public Entity {
public:
	Water();
};

#endif
