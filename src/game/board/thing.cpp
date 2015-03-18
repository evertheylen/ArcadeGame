#include "thing.h"
#include "../../DesignByContract.h"

Thing::Thing() {
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

Thing::Thing(unsigned int x, unsigned int y, int weight):
	_x(x), _y(y), _weight(weight)
	{
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Thing::Thing(const Thing& that):
	_x(that._x),
	_y(that._y),
	_weight(that._weight) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Thing& Thing::operator=(const Thing& that) {
	_x = that._x;
	_y = that._y;
	_weight = that._weight;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

bool Thing::properlyInitialized() const {
	return _initCheck == this;
}

bool Thing::is_movable() const {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling is_movable");
	return _weight>=0;
}

int Thing::get_weight() const {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_weight");
	int result = _weight;
	return result;
}

void Thing::set_weight(int weight) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_weight");
	_weight = weight;
	ENSURE(get_weight() == weight, "Incorrect weight specified");
}

unsigned int Thing::get_x() const {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_x");
	unsigned int result = _x;
	ENSURE(result >= 0, "Incorrect x coordinate returned");
	return result;
}

void Thing::set_x(unsigned int x) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_x");
	_x = x;
	ENSURE(get_x() == x && x >= 0, "Incorrect x specified");
}

unsigned int Thing::get_y() const {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_y");
	unsigned int result = _y;
	ENSURE(result >= 0, "Incorrect y coordinate returned");
	return result;
}

void Thing::set_y(unsigned int y) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_y");
	_y = y;
	ENSURE(get_y() == y && y >= 0, "Incorrect y specified");
}

/*void Thing::print(){
	std::cout << "Thing" << std::endl;
}*/

std::ostream& Thing::print(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling print");
	out << "Thing" << std::endl;
	return out;
}

std::ostream& operator<< (std::ostream &out, Thing &thing){
	REQUIRE(thing.properlyInitialized(), "Thing wasn't initialized when calling operator <<");
	thing.print(out);
	return out;
}

char Thing::to_char() {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling to_char");
	return 'T';
}
