/*
 * actor.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include <string>

#include "ia/none.h"
#include "life/alive.h"
#include "physics/solid.h"
#include "printer/lifeprinter.h"
#include "entity.h"

#ifndef _H_Actor
#define _H_Actor


class Actor: public None, public Alive, public Solid, public LifePrinter, public Entity {
public:
	Actor(unsigned int x, unsigned y, char print, std::string _name);
	
	std::string get_name();
	
private:
	std::string name;
};

#endif
