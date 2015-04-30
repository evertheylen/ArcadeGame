
#ifndef _H_Move
#define _H_Move

#include "actions.h"

class Move: public Action {
public:
	Move(Actor* _actor, std::string& dirname);
	
	void execute(Game* g);
};


#endif
