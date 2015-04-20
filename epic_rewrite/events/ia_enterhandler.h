#include "dispatch/dispatchers.h"
#include "entity.h"

#include "handler.h"

#ifndef _H_IA_EnterHandler
#define _H_IA_EnterHandler

class Game;

class IA_EnterHandler: public Handler {
public:
	void onEnter(Entity* p, Entity* m);
};



#endif
