/*
 * monster.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/alive.h"
#include "physics/simplephysics.h"
#include "printer/lifeprinter.h"
#include "ia/none.h"

#ifndef _H_Monster
#define _H_Monster

class Monster: public None, public Alive, public SimplePhysics, public LifePrinter, public Entity {
public:
	Monster(unsigned int x, unsigned y);
};

#endif
