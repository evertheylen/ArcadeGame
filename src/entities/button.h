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

#include "../events/ia_enterhandler.h"
#include "../events/ia_leavehandler.h"

#ifndef _H_Button
#define _H_Button

class Button: public Immutable, public Small, public SimplePrint, public Entity {
public:
	Button(unsigned int x, unsigned y, Gate* _gate);
	void info(std::ostream& out);
	
	// spec: Interactive
	friend class IA_EnterHandler;
	friend class IA_LeaveHandler;
	
private:
	Gate* gate;
};

#endif

