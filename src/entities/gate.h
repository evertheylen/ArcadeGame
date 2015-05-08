/*
 * gate.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "entity.h"
#include <string>

#include "life/immutable.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Gate
#define _H_Gate

class Gate: public None, public Immutable, public Entity {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Gate(unsigned int x, unsigned y, std::string _name);		// TODO Add functionality to link a button
	
	// spec: Physics

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling get_height")*/
	int get_height();

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling get_weight")*/
	int get_weight();
	
	// spec: Printer

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling to_char")*/
	char to_char();
	
	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling get_name")*/
	std::string& get_name();

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling open")
	 * ENSURE(_open == true, "Gate wasn't opened when calling open")*/
	void open();

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling close")
	 * ENSURE(_open == false, "Gate wasn't closed when calling close")*/
	void close();
	

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling info")*/
	void info(std::ostream& out);

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling save")*/
	void save(std::ostream& out, int x, int y);

	/**REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling is_open")*/
	bool is_open();

private:
	bool _open;
	std::string name;
};

#endif
