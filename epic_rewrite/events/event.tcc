
#include "../game/game.h"
#include "event.h"

template <typename A, typename B>
class Collision: public Event {
private:
	A& a;
	B& b;
	
public:
	Collision(A& _a, B& _b):
			a(_a), b(_b) {}

	void handle(Game* g) {
		g->event_log("Collision between two objects");
	}
};

template <typename A>
class Death: public Event {
private:
	A& a;

public:
	Death(A& _a):
			a(_a) {}
	
	void handle(Game* g) {
		g->event_log("Oh no, something died");
	}
};
