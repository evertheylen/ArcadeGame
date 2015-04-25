#include "dispatch/dispatchers.h"
#include "entity.h"
#include "player.h"
#include "alive.h"

#include "handler.h"

#ifndef _H_KillHandler
#define _H_KillHandler

class Game;

class KillHandler: public Handler {
public:
	void onKill(Player* p);
	void onKill(Alive* a);
	void onKill(Entity* e);
};



#endif
