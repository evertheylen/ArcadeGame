#include "boobytrap.h"
#include "../../DesignByContract.h"

Boobytrap::Boobytrap(unsigned int x, unsigned int y):
	Thing(x,y,BOOBYTRAP_WEIGHT,BOOBYTRAP_HEIGHT,BOOBYTRAP_IMPORTANCE)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of boobytrap");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Boobytrap::Boobytrap(const Boobytrap& that):
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Boobytrap& Boobytrap::operator=(const Boobytrap& that) {
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Boobytrap::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling print");
	out << "Boobytrap\n";
	return out;
}

char Boobytrap::to_char() {
	REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling print");
	return ' ';
}

void Boobytrap::onEnter(MovableThing* other) {
	if (_alive) {
		other->kill();
		Life::kill();
	}
}
