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
	ENSURE(result == _weight && result >= -1, "Incorrect weight or no weight at all returned");
	return result;
}

void Thing::set_weight(int weight) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_weight");
	_weight = weight;
	ENSURE(_weight == weight && weight >= -1, "Incorrect weight specified");
}

unsigned int Thing::get_x() const {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_x");
	unsigned int result = _x;
	ENSURE(result == _x && _x >= 0, "Incorrect x coordinate returned");
	return result;
}

void Thing::set_x(unsigned int x) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_x");
	_x = x;
	ENSURE(_x == x && x >= 0, "Incorrect x specified");
}

unsigned int Thing::get_y() const {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_y");
	unsigned int result = _y;
	ENSURE(result == _y && _y >= 0, "Incorrect y coordinate returned");
	return result;
}

void Thing::set_y(unsigned int y) {
	REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_y");
	_y = y;
	ENSURE(_y == y && y >= 0, "Incorrect y specified");
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
