
#include "simplephysics.h"

SimplePhysics::SimplePhysics(int _height, int _weight):
		height(_height), weight(_weight) {}

int SimplePhysics::get_height() {
	return height;
}

int SimplePhysics::get_weight() {
	return weight;
}
