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

	Small();		//TODO Make this what you want...

	int get_height();
	int get_weight();

private:
	int height;
	int weight;
};

#endif
