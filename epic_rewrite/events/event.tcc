/*
#include "../game/game.h"
#include "../entities/water.h"
#include "event.h"

template <typename A, typename B>
class Collision: public Event {
protected:
	A& a;
	B& b;
	
public:
	Collision(A& _a, B& _b):
			a(_a), b(_b) {}

	void handle(Game* g) {
		g->event_log("Collision between two objects");
	}
};

template <typename B>
class Collision<Water, B> {
private:
	Water& a;
	B& b;

public:
	Collision(Water& _a, B& _b):
			a(_a), b(_a) {}
	
	void handle(Game* g) {
		g->event_log("Sploosh");
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
*/
