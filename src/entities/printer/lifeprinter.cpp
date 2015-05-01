
#include "lifeprinter.h"

LifePrinter::LifePrinter(char _alive, char _dead):
		symbol_alive(_alive), symbol_dead(_dead) {}

char LifePrinter::to_char() {
	if (is_alive()) {
		return symbol_alive;
	} else {
		return symbol_dead;
	}
}
