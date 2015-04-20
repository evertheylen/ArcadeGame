/*
 * button.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "entity.h"
#include "gate.h"

#include "life/immutable.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Button
#define _H_Button

class Button: public None, public Immutable, public Small, public SimplePrint, public Entity {
public:
	Button(Gate* g);		//TODO IA Die ervoor zorgt dat een poort opent! voorlopig nog NONE.

private:
	Gate* _g;
};

#endif

