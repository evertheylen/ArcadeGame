/*
 * monster.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "actor.h"

#include "life/alive.h"
#include "physics/simplephysics.h"
#include "printer/lifeprinter.h"
#include "ia/none.h"

#ifndef _H_Monster
#define _H_Monster

class Monster: public Actor {
public:
	Monster(unsigned int x, unsigned y);
};

#endif
