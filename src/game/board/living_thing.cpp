#include "living_thing.h"
#include "../../DesignByContract.h"


LivingThing::LivingThing(unsigned int x, unsigned int y, int weight, int height, int importance, int maximum_weight, std::string name):
	MovableThing(x, y, weight, height, importance, LIVINGTHING_SOLIDNESS), _maximum_weight(maximum_weight), _name(name)
	{
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
LivingThing::LivingThing(const LivingThing& that):
	_name(that._name),
	_maximum_weight(that._maximum_weight),
	MovableThing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}


// copy assignment
LivingThing& LivingThing::operator=(const LivingThing& that) {
	_name = that._name;
	_maximum_weight = that._maximum_weight;
	MovableThing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

void LivingThing::kill() {
	Life::kill();
	_importance = -1;
}

char LivingThing::to_char() {
	return 'L';
}

std::string LivingThing::get_name() {
	return _name;
}

int LivingThing::get_maximum_weight() {
	REQUIRE(properlyInitialized(), "LivingThing wasn't initialized when calling get_maximum_weight");
	int result = _maximum_weight;
	return result;
}

void LivingThing::set_maximum_weight(int max) {
	REQUIRE(properlyInitialized(), "LivingThing wasn't initialized when calling set_maximum_weight");
	_maximum_weight = max;
	ENSURE(get_maximum_weight() == max, "Maximum_weight wasn't correctly set!");
}

std::string LivingThing::get_typename() {
	return "LivingThing";
}
