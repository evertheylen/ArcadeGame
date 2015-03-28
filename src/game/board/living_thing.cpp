#include "living_thing.h"
#include "../../DesignByContract.h"


LivingThing::LivingThing(unsigned int x, unsigned int y, int weight, int height, int importance, int maximum_weight):
	MovableThing(x, y, weight, height, importance, LIVINGTHING_SOLIDNESS), _maximum_weight(maximum_weight),
	_alive(true)
	{
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// TODO copy ctor, copy assign


void LivingThing::kill() {
	_alive = false;
	_importance = -1;
}

char LivingThing::to_char() {
	return 'L';
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

bool LivingThing::is_alive() {
	return _alive;
}
