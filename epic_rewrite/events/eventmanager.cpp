/*

#include "eventmanager.h"
#include "../game/game.h"
#include "event.h"
#include <typeinfo>

#ifdef __GNUG__
	// from 
	#include <iostream>
	#include <cxxabi.h>

	template<typename T>
	std::string type_name(T obj)
	{
		int status;
		std::string tname = typeid(obj).name();
		std::cout << "bad name: " << tname << "\n";
		char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
		std::cout << "better name: " << demangled_name << "\n";
		if(status == 0) {
			tname = demangled_name;
			std::free(demangled_name);
		}
		return tname;
	}
#endif

EventManager::EventManager(std::ostream& _logstream):
		logstream(_logstream), g(nullptr), state("") {}

void EventManager::set_game(Game* _g) {
	g = _g;
}


void EventManager::log(std::string s) {
	logstream << "[" << state << "] " << s << "\n";
}

void EventManager::push(Event& e) {
	#ifdef __GNUG__
		state = std::string("handling ") + type_name(e);
	#else
		state = std::string("handling ") + typeid(e).name();
	#endif
	
	e.handle(g);
}

*/
