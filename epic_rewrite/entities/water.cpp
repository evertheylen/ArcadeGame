
#include "water.h"

Water::Water(unsigned int x, unsigned y):
		Entity(x, y), contained(nullptr) {}

char Water::to_char() {
	if (contained == nullptr)
		return '~';
	else
		return ' ';
}


int Water::get_height() {
	if (contained == nullptr)
		return WATER_HEIGHT;
	else
		return 0;
}

int Water::get_weight() {
	if (contained == nullptr)
		return WATER_WEIGHT;
	else
		return WATER_WEIGHT+contained->get_weight();
}

