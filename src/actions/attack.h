
#ifndef _H_Attack
#define _H_Attack

#include "actions.h"

class Attack: public Action {
public:
	Attack(Player* player, std::string& dirname);
	
	bool execute(Game* g);

	void save(std::ostream& out);
};


#endif
