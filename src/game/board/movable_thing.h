/*
 * movable_thing.h
 *
 *  Created on: 27 Mar 2015
 *      Author: stijn & evert
 */

#ifndef _MovableThing
#define _MovableThing

#include "thing.h"

class MovableThing: public Thing {
public:
	MovableThing(unsigned int x, unsigned int y, int weight, int height, int importance, bool solid);
	
	//! copy constructor
	MovableThing(const MovableThing& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	MovableThing& operator=(const MovableThing& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/
	
	virtual char to_char();
	
	bool is_solid();
	
	virtual void end_game(); // may end the game (only player)
	
private:
	bool _solid;
};



#endif /* _MovableThing */
