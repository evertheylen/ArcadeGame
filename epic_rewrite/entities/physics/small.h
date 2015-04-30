/*
 * small.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn & evert
 */

#include "physics.h"

#ifndef _H_Small
#define _H_Small

class Small: public virtual Physics {
public:
	int get_height();
	int get_weight();
};

#endif
