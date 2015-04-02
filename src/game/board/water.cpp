#include "water.h"
#include "../../DesignByContract.h"

Water::Water(unsigned int x, unsigned int y):
	Thing(x,y,WATER_WEIGHT,WATER_HEIGHT,WATER_IMPORTANCE),
	_filled(false)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of water");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Water::Water(const Water& that):
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Water& Water::operator=(const Water& that) {
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Water::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling print");
	out << "Water\n";
	return out;
}

char Water::to_char() {
	REQUIRE(properlyInitialized(), "Water wasn't initialized when calling print");
	return '~';
}

void Water::onEnter(MovableThing* other) {
	if (! _filled) {
		other->kill();
		// if it's still alive, it's immutable
		if (other->is_alive() && other->is_solid()) {
			_filled = true;
		}
	}
}