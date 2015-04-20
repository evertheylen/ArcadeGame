/*
 * small.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "physics.h"

#ifndef _H_Small
#define _H_Small

class Small: public virtual Physics {
public:

	Small(unsigned int _x, unsigned int _y);		//TODO Make this what you want...

	int get_height();
	int get_weight();

	unsigned int get_x();
	unsigned int get_y();

private:
	int height;
	int weight;
	unsigned int x;
	unsigned int y;
};

#endif
