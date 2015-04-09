/*
 * gate.h
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "thing.h"
#include <string>

#ifndef GAME_BOARD_GATE_H_
#define GAME_BOARD_GATE_H_

class Gate: public Thing {
public:
	static const int GATE_WEIGHT = 1000;
	static const int GATE_HEIGHT = 100;
	static const int GATE_IMPORTANCE = 1050;


	//! copy constructor
	Gate(const Gate& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Gate& operator=(const Gate& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Gate(unsigned int x, unsigned int y, std::string ID);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	void set_height(int height);

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");*/

	char to_char();
	/**< REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling to_char");*/
	
	std::string get_ID();
	
private:
	std::string _ID;
};



#endif /* GAME_BOARD_GATE_H_ */
