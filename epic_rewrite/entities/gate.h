/*
 * gate.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/immutable.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Gate
#define _H_Gate

class Gate: public None, public Immutable, public Entity {
public:
	Gate(unsigned int x, unsigned y);		// TODO Add functionality to link a button
	
	// spec: Physics
	int get_height();
	int get_weight();
	
	// spec: Printer
	char to_char();
	
	void open();
	void close();
	
	bool is_open();

private:
	bool _open;
};

#endif
