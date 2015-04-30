
#include "printer.h"

#ifndef _H_Simpleprint
#define _H_Simpleprint

class SimplePrint: public virtual Printer {
public:
	SimplePrint(char s);
	
	char to_char();
	
private:
	char symbol;
};

#endif
