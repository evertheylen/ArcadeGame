/*
 * spot.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include <vector>
#include "thing.h"
#include "movable_thing.h"

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
	
	int get_height();
	
	MovableThing* get_upper();

	// tgeen dater onder zit
	void add_stuff(Thing* thing);
	
	// die movablething enzo, returned true als het fallthroughed naar lower level.
	bool add_upper(MovableThing* thing);
	/**< REQUIRE(_upper == nullptr, "_upper is occupied"); */
	
	void del_upper();
	
	char to_char();

	void writeThings(std::ostream& stream);

	bool properlyInitialized();

private:
	unsigned int _x;
	unsigned int _y;
	Spot* _initCheck;
	
	Thing* most_important_thing();

	MovableThing* _upper;
	std::vector<Thing*> _stuff; // finally.
};



#endif /* _Spot */
