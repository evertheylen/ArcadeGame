
#include "printer.h"
#include "../life/life.h"

#ifndef _H_LifePrinter
#define _H_LifePrinter

class LifePrinter: public virtual Printer, public virtual Life {
public:
	LifePrinter(char _alive, char _dead);
	
	char to_char();
	
private:
	char symbol_alive;
	char symbol_dead;
};

#endif
