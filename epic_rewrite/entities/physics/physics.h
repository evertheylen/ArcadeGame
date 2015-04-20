
#ifndef _H_Physics
#define _H_Physics

class Physics {
public:
	virtual void __polymorphic__() {}
	
	virtual int get_height() = 0;
	virtual int get_weight() = 0;

	virtual ~Physics() {}
};

#endif
