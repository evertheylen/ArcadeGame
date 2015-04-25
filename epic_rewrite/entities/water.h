
#include "entity.h"

#include "life/immutable.h"
#include "physics/solid.h"
#include "printer/simpleprint.h"
#include "ia/lethal.h"

#ifndef _H_Water
#define _H_Water

class Water: public Lethal, public Immutable, public Entity {
public:
	static const int WATER_HEIGHT = -100;
	static const int WATER_WEIGHT = 500;
	
	Water(unsigned int x, unsigned y);
	
	bool is_filled();
	
	// spec: Printer
	char to_char();
	
	// spec: Physics
	int get_weight();
	int get_height();
	
	// Has to be both getted and setted, so easier to maintain as a public variable
	Entity* contained;
};

#endif
