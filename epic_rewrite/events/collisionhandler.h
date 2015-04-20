#include "dispatch/dispatchers.h"
#include "player.h"
#include "entity.h"
#include "monster.h"

#include "handler.h"

#ifndef _H_CollisionHandler
#define _H_CollisionHandler

class Game;

// Inherited by CollisionDispatcher
class CollisionHandler: public Handler {
public:
	int onCollision(Player* p, Monster* m);
	int onCollision(Entity* e, Entity* f);
};



#endif
