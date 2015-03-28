/*
 * monster.h
 *
 *  Created on: 27 Mar 2015
 *      Author: stijn & evert
 */

#include "living_thing.h"
#include "movable_thing.h"
#include "barrel.h"

#ifndef _Monster
#define _Monster

class Monster: public LivingThing {
public:
	// Constants
	static const int  MONSTER_WEIGHT = 0;
	static const int  MONSTER_HEIGHT = 0;
	static const int  MONSTER_IMPORTANCE = 950;
	static const int  MONSTER_MAXIMUM_WEIGHT = Barrel::BARREL_WEIGHT;
	
	
	//! copy constructor
	Monster(const Monster& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Monster& operator=(const Monster& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Monster(std::string name = "Bowser", unsigned int x = 0, unsigned int y = 0);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments for constructor of player.");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	const std::string& get_name() const;
	/**< REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling get_name");*/

	void set_name(const std::string& name);
	/**< REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling set_name");
		ENSURE(get_name() == name, "name wasn't correctly set!");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling print");*/
	
	char to_char();
	/**< REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling to_char");*/
	
	void onEnter(MovableThing* other);
	
	void onLeave(MovableThing* other);
	
	~Monster() {}

private:
	std::string _name;

};


#endif /* _Monster */
