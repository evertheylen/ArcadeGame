#include "dispatch/dispatchers.h"
#include "player.h"
#include "entity.h"
#include "monster.h"

#include "handler.h"

#ifndef _H_CollisionHandler
#define _H_CollisionHandler

class Game;
class Water;

// Inherited by CollisionDispatcher
class CollisionHandler: public Handler {
public:
	void onCollision(Player* p, Monster* m);
	void onCollision(Water* w, Entity* e);
	void onCollision(Entity* e, Entity* f);
};



#endif
