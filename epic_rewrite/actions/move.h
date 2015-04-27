
#ifndef _H_Attack
#define _H_Attack

#include "actions.h"

class Move: public Action {
public:
	Move(Actor* _actor, std::string& dirname);
	
	void execute(Game* g);
};


#endif
