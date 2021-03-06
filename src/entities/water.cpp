
#include "water.h"
#include "constants.h"

Water::Water(unsigned int x, unsigned y):
		Entity(x, y), contained(nullptr) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

bool Water::is_filled() {
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling is_filled");
	return contained != nullptr;
}


char Water::to_char() {
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling to_char");
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
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling get_height");
	if (contained == nullptr)
		return WATER_HEIGHT;
	else
		return 0;
}

int Water::get_weight() {
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling get_weight");
	if (contained == nullptr)
		return WATER_WEIGHT;
	else
		return WATER_WEIGHT + contained->get_weight();
}

void Water::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling info");
	out << "Er bevindt zich water op positie (" << x << "," << y << ")\n";
}

void Water::save(std::ostream& out, int x, int y) {
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling save");
	out << "<WATER beweegbaar=\"false\" x=\"" << x << "\" y=\"" << y << "\" contained=\"true\">\n";
	out << "\t\t<CONTAINED>";
}

Water::~Water() {
	delete contained;
}
