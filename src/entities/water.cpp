
#include "water.h"
#include "constants.h"

Water::Water(unsigned int x, unsigned y):
		Entity(x, y), contained(nullptr) {}

bool Water::is_filled() {
	return contained != nullptr;
}


char Water::to_char() {
	if (contained == nullptr) {
		return WATER_SYMBOL_EMPTY;
	} else {
		if (contained->get_height()+WATER_HEIGHT < 0)
			return WATER_SYMBOL_EMPTY;
		else
			return WATER_SYMBOL_FULL;
	}
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
		return WATER_WEIGHT + contained->get_weight();
}

void Water::info(std::ostream& out) {
	out << "Er bevindt zich water op positie (" << x << "," << y << ")\n";
}
