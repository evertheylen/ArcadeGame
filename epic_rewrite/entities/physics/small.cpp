/*
 * small.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "small.h"

Small::Small(unsigned int _x, unsigned int _y): height(0), weight(0), x(_x), y(_y) {}

int Small::get_height() {
	return height;
}

int Small::get_weight() {
	return weight;
}

unsigned int Small::get_x() {
	return x;
}

unsigned int Small::get_y() {
	return y;
}
