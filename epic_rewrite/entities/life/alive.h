/*
 * alive.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */
#include "life.h"

#ifndef _H_Alive
#define _H_Alive

class Alive: public virtual Life {
public:
	Alive(int lives);

	bool is_alive();
	void kill();

private:
	int _lives;
};

#endif

