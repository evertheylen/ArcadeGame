#include "dispatch/dispatchers.h"
#include "entity.h"
#include "goal.h"
#include "player.h"
#include "actor.h"
#include "boobytrap.h"

#include "handler.h"

#ifndef _H_IA_EnterHandler
#define _H_IA_EnterHandler

class Game;
class Button;

class IA_EnterHandler: public Handler {
public:
	void onEnter(Player* p, Goal* g);
	void onEnter(Actor* a, Boobytrap* b);
	void onEnter(Entity* e, Button* b);
	void onEnter(Entity* e, Entity* f);
};



#endif
