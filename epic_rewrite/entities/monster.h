/*
 * monster.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/life.h"
#include "physics/simplephysics.h"
#include "printer/lifeprinter.h"
#include "ia/none.h"

#ifndef _H_Monster
#define _H_Monster

class Monster: public None, public Life, public SimplePhysics, public LifePrinter, public Entity {
public:
	Monster();
};

#endif
