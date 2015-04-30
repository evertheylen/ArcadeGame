
#include "life.h"

#ifndef _H_Immutable
#define _H_Immutable

class Immutable: public virtual Life {
public:
	bool is_alive();
	void kill();
};

#endif
