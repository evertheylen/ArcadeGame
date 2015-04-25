
#include "ia_leavehandler.h"
#include "button.h"

void IA_LeaveHandler::onLeave(Entity* e, Entity* f) {
	// do stuff
}

void IA_LeaveHandler::onLeave(Entity* e, Button* b) {
	b->gate->close();
}


