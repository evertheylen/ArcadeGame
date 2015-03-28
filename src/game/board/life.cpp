#include "life.h"
#include "../../DesignByContract.h"


Life::Life(): _alive(true) {}

void Life::kill() {
	_alive = false;
}


bool Life::is_alive() {
	return _alive;
}
