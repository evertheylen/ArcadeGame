/*
 * boobytrap.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/alive.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Boobytrap
#define _H_Boobytrap

class Boobytrap: public None, public Alive, public Small, public SimplePrint, public Entity {
public:
	Boobytrap();		//TODO Voorlopig is IA == none, dit moet worden dat het bij een collision 1 keer lethal is en dan zelf gedestruct wordt!
	// Ik heb dit simpleprint ipv lifeprint gemaakt omdat boobytrap altijd onzichtbaar is!
};

#endif

