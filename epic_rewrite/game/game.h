
#ifndef _Game
#define _Game

#include <iostream>
#include "../events/eventmanager.h"

class Game {
private:
	EventManager em;

public:
	Game(EventManager _em);
	
	void event_log(std::string s);
	
	void main_loop();
};

#endif
