
#ifndef _Printer
#define _Printer

class Printer {
public:
	virtual void __polymorphic__() {}
	
	virtual char to_char() = 0;
	
	virtual ~Printer() {}
};

#endif
