
#include "simplephysics.h"

SimplePhysics::SimplePhysics(int _height, int _weight, unsigned int _x, unsigned int _y):
		height(_height), weight(_weight), x(_x), y(_y) {}

int SimplePhysics::get_height() {
	return height;
}

int SimplePhysics::get_weight() {
	return weight;
}

unsigned int SimplePhysics::get_x() {
	return x;
}

unsigned int SimplePhysics::get_y() {
	return y;
}
