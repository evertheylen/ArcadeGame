/*
 * movable_thing.h
 *
 *  Created on: 27 Mar 2015
 *      Author: stijn & evert
 */

#include "thing.h"

#ifndef _Movable_thing
#define _Movable_thing

class Movable_thing: public Thing {
public:
	Movable_thing(unsigned int x, unsigned int y, int weight);
};



#endif /* _Movable_thing */
