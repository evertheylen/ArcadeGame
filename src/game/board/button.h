/*
 * button.h
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "thing.h"
#include "gate.h"

#ifndef GAME_BOARD_BUTTON_H_
#define GAME_BOARD_BUTTON_H_

class Button: public Thing {
public:
	static const int BUTTON_WEIGHT = 100;
	static const int BUTTON_HEIGHT = 0;
	static const int BUTTON_IMPORTANCE = 100;


	//! copy constructor
	Button(const Button& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Button& operator=(const Button& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Button(unsigned int x, unsigned int y, Gate* gate);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");*/

	void onEnter(MovableThing* other);

	void onLeave(MovableThing* other);

	char to_char();
	/**< REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling to_char");*/

private:
	Gate* _gate;
};



#endif /* GAME_BOARD_BUTTON_H_ */
