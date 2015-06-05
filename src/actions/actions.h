
#ifndef _H_Action
#define _H_Action

#include <iostream>
#include <string>
#include "../entities/actor.h"
#include "../entities/player.h"
#include "../entities/monster.h"

class Game;

class Direction {
public:
	enum class Dirk {up, left, down, right, no_dir};
	
	/**
	 * ENSURE(properlyInitialized(), "Constructor must end...")
	 */
	Direction(std::string& s);

	/**
	 * ENSURE(properlyInitialized(), "Constructor must end...")
	 */
	Direction(Dirk d);
	
	/** \brief Copy constructor
	 *
	 * ENSURE(properlyInitialized(), "Copy constructor must end...")
	 */
	Direction(const Direction& that);

	/** \brief Copy by assignment
	 *
	 * ENSURE(properlyInitialized(), "Copy by assignment must end...")
	 */
	Direction& operator=(const Direction& that);

	/**
	 * REQUIRE(d.properlyInitialized(), "Direction wasn't initialized when calling operator <<.")
	 */
	friend std::ostream& operator<<(std::ostream& out, Direction& d);
	
	/**
	 * REQUIRE(properlyInitialized(), "Direction wasn't initialized when calling get_dir.")
	 */
	Direction::Dirk get_dir();

	/**
	 * REQUIRE(properlyInitialized(), "Direction wasn't initialized when calling move_to.")
	 */
	void move_to(unsigned int& x, unsigned int& y);

	/**
	 * REQUIRE(properlyInitialized(), "Direction wasn't initialized when calling move_from.")
	 */
	void move_from(unsigned int& x, unsigned int& y);
	
	bool properlyInitialized();

private:
	Dirk dir;
	Direction* initCheck;
};


class Action {
protected:
	Actor* actor;
	Direction dir;
	Action* initCheck;
	
public:
	/**
	 * ENSURE(properlyInitialized(), "Constructor must end...")
	 */
	Action(Actor* _actor, std::string& dirname);
	
	/** \brief Copy constructor
	 *
	 * ENSURE(properlyInitialized(), "Copy constructor must end...")
	 */
	Action(const Action& that);

	/** \brief Copy by assignment
	 *
	 * ENSURE(properlyInitialized(), "Copy by assignment must end...")
	 */
	Action& operator=(const Action& that);

	/**
	 * REQUIRE(properlyInitialized(), "Action wasn't initialized when calling get_actor.")
	 */
	Actor* get_actor();

	/**
	 * REQUIRE(properlyInitialized(), "Action wasn't initialized when calling get_dir.")
	 */
	Direction get_dir();

	virtual bool execute(Game* g) = 0;

	/**
	 * REQUIRE(d.properlyInitialized(), "Action wasn't initialized when calling save.")
	 */
	virtual void save(std::ostream& out) = 0;

	bool properlyInitialized();
	
	virtual ~Action() {};
};



#endif
