#include<iostream>

#ifndef _H_Printer
#define _H_Printer

class Printer {
public:
	virtual void __polymorphic__() {}
	
	virtual char to_char() = 0;
	
	virtual ~Printer() {}
};

#endif
