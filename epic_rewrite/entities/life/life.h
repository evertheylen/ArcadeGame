
#ifndef _Life
#define _Life

class Life {
public:
	virtual void __polymorphic__() {}

	virtual bool is_alive() = 0;
	virtual void kill() = 0;
	
	virtual ~Life() {}
};

#endif
