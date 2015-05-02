
#include "entity.h"

Entity::Entity(unsigned int _x, unsigned int _y):
		x(_x), y(_y) {
	initCheck = this;
	ENSURE(properlyInitialized(), "Constructor must end...");
}

bool Entity::properlyInitialized() {
	return (initCheck == this);
}

Entity::Entity(const Entity& that) {
	x = that.x;
	y = that.y;
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

Entity& Entity::operator=(const Entity& that) {
	x = that.x;
	y = that.y;
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}
