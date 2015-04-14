
#include "printer.h"

#ifndef _Simpleprint
#define _Simpleprint

class SimplePrint: public virtual Printer {
public:
	SimplePrint(char s);
	
	char to_char();
	
private:
	char symbol;
};

#endif
