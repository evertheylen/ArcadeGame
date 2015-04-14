
#include "entity.h"

#include "life/immutable.h"
#include "physics/container.h"
#include "printer/simpleprint.h"
#include "ia/lethal.h"

#ifndef _Water
#define _Water

class Water: public Immutable, public Container, public SimplePrint, public Lethal, public Entity {
public:
	Water();
};

#endif
