/*
#include <iostream>
#include <string>

#ifndef _H_EventManager
#define _H_EventManager

class Game;
class Event;

class EventManager {
private:
	std::ostream& logstream;
	std::string state;
	Game* g;
	
public:
	void set_game(Game* _g);
	
	EventManager(std::ostream& _logstream);

	void push(Event& e);
	
	void log(std::string s);
};


#endif
*/
