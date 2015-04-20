
#include "dispatch/dispatchers.h"

#ifndef _H_Collisionmanager
#define _H_Collisionmanager

class Game;

class CollisionManager: public CollisionDispatch {
public:
	CollisionManager(Game* g);
};

#endif
