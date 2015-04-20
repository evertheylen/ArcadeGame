
#include "solid.h"

Solid::Solid(int _height, int _weight):
		height(_height), weight(_weight) {}

int Solid::get_height() {
	return height;
}

int Solid::get_weight() {
	return weight;
}
