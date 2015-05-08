
#include "immutable.h"

bool Immutable::is_alive() {
	return true;
}

int Immutable::get_lives() {
	return 1;
}

void Immutable::kill() {
	// I'm immutable, bitches!
}

