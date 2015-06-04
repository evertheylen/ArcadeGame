
#ifndef _H_Attack
#define _H_Attack

#include "actions.h"

class Attack: public Action {
public:
	/**
	 * ENSURE(properlyInitialized(), "Constructor must end...")
	 */
	Attack(Player* player, std::string& dirname);
	
	/**
	 * REQUIRE(properlyInitialized(), "Attack wasn't initialized when calling execute.")
	 */
	bool execute(Game* g);

	/**
	 * REQUIRE(properlyInitialized(), "Attack wasn't initialized when calling save.")
	 */
	void save(std::ostream& out);
};


#endif
