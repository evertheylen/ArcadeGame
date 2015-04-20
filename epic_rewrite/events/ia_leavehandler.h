#include "dispatch/dispatchers.h"
#include "entity.h"

#include "handler.h"

#ifndef _H_IA_LeaveHandler
#define _H_IA_LeaveHandler

class Game;

class IA_LeaveHandler: public Handler {
public:	
	void onLeave(Entity* e, Entity* f);
};

#endif
