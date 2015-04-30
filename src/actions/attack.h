
#ifndef _H_Attack
#define _H_Attack

#include "actions.h"

class Attack: public Action {
public:
	Attack(Player* player, std::string& dirname);
	
	void execute(Game* g);
};


#endif
