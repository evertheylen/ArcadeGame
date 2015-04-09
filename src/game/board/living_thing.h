#include "movable_thing.h"
#include "life.h"
#include <string>

#ifndef _LivingThing
#define _LivingThing

class LivingThing: public MovableThing, public Life {  // Multiple inheritance FTW
public:
	static const bool LIVINGTHING_SOLIDNESS = true;

	LivingThing(unsigned int x, unsigned int y, int weight, int height, int importance, int maximum_weight, std::string name = "Mario");
	
	//! copy constructor
	LivingThing(const LivingThing& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	LivingThing& operator=(const LivingThing& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/
	
	void kill();
	
	virtual char to_char();
	
	int get_maximum_weight();
	void set_maximum_weight(int max);
	
	std::string get_name();
	
	virtual std::string get_typename();

protected:
	int _maximum_weight;
	std::string _name;
};



#endif /* _LivingThing */
