
#ifndef _H_Move
#define _H_Move

#include "actions.h"

class Move: public Action {
public:
	/**
	 * ENSURE(properlyInitialized(), "Constructor must end...")
	 */
	Move(Actor* _actor, std::string& dirname);
	
	/**
	 * REQUIRE(properlyInitialized(), "Move wasn't initialized when calling execute.")
	 */
	bool execute(Game* g);

	/**
	 * REQUIRE(properlyInitialized(), "Move wasn't initialized when calling save.")
	 */
	void save(std::ostream& out);
};


#endif
