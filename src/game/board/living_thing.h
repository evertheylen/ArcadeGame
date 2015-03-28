#include "movable_thing.h"

#ifndef _LivingThing
#define _LivingThing

class LivingThing: public MovableThing {
public:
	static const bool LIVINGTHING_SOLIDNESS = true;

	LivingThing(unsigned int x, unsigned int y, int weight, int height, int importance, int maximum_weight);
	
	// TODO copy ctor, copy assign
	
	void kill();
	
	virtual char to_char();
	
	bool is_alive();
	
	int get_maximum_weight();
	void set_maximum_weight(int max);
	
protected:
	bool _alive;
	int _maximum_weight;
};



#endif /* _LivingThing */
