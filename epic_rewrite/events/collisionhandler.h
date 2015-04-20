#include "dispatch/dispatchers.h"
#include "player.h"
#include "entity.h"
#include "monster.h"

#ifndef _H_CollisionManager
#define _H_CollisionManager

class Game;

// Inherited by CollisionDispatcher
class CollisionHandler {
private:
	Game* game;
	
public:
	void setGame(Game* _g);
	
	int onCollision(Player* p, Monster* m);
	int onCollision(Entity* e, Entity* f);
};



#endif
