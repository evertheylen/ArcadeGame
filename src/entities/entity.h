
#include "ia/ia.h"
#include "life/life.h"
#include "physics/physics.h"
#include "printer/printer.h"
#include "DesignByContract.h"

#ifndef _H_Entity
#define _H_Entity

// If you don't like multiple inheritance, you should stop reading right now and find some other
// project you like. I'm serious. Also, if you don't like virtuals or RTTI in general, consider
// rm -rf'ing your local copy of this project, and then watching some cat gifs.

// If you _do_ like MI and RTTI, buckle up, this is going to be quite a ride.

class Entity: public virtual Interactive, public virtual Life, public virtual Physics, public virtual Printer {
public:
	virtual void __polymorphic__() {}
	
	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Entity(unsigned int _x, unsigned int _y);
	
	/** \brief Copy constructor
	 *
	 * ENSURE(properlyInitialized(), "Copy constructor must end...")
	 */
	Entity(const Entity& that);

	/** \brief Copy by assignment
	 *
	 * ENSURE(properlyInitialized(), "Copy by assignment must end...")
	 */
	Entity& operator=(const Entity& that);

	/** Shows the info about the entity, used in the method Board::write_board.
	 * Is a pure virtual function for Entity.
	 * REQUIRE(properlyInitialized(), "Entity wasn't initialized when calling info")
	 */
	virtual void info(std::ostream& out) = 0;

	/** Saves the entity, used in the method Game::save.
	 * Is a pure virtual function for Entity.
	 * REQUIRE(properlyInitialized(), "Entity wasn't initialized when calling save")
	 */
	virtual void save(std::ostream& out, int x, int y) = 0;

	virtual ~Entity() {}
	
	// x and y can be both getted and setted, so it's better to make them public anyways.
	unsigned int x;
	unsigned int y;

	bool properlyInitialized();

private:
	Entity* initCheck;
};

#endif
