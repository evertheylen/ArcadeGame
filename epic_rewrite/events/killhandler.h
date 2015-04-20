#include "dispatch/dispatchers.h"
#include "entity.h"
#include "player.h"

#include "handler.h"

#ifndef _H_KillHandler
#define _H_KillHandler

class Game;

class KillHandler: public Handler {
public:
	void onKill(Entity* e);
	void onKill(Player* p);
};



#endif
