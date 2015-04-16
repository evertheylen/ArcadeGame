
#ifndef _H_Life
#define _H_Life

class Life {
public:
	virtual void __polymorphic__() {}

	virtual bool is_alive() = 0;
	virtual void kill() = 0;
	
	virtual ~Life() {}
};

#endif
