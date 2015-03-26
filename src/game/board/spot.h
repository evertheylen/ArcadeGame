/*
 * spot.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include <vector>
#include "thing.h"

#ifndef _Spot
#define _Spot

class Spot {
public:
	Spot(unsigned int x, unsigned int y);
	/**< ENSURE(properlyInitialized(), "Constructor must end..."); */

	//! copy constructor
	Spot(const Spot& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Spot& operator=(const Spot& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	unsigned int get_x();

	unsigned int get_y();

	void add_stuff(Thing* thing);

	bool properlyInitialized();

private:
	unsigned int _x;
	unsigned int _y;
	Spot* _initCheck;
	std::vector<Thing*> _stuff; //finally.
};



#endif /* _Spot */
