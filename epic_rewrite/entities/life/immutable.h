
#include "life.h"

#ifndef _Immutable
#define _Immutable

class Immutable: public virtual Life {
public:
	bool is_alive();
	void kill();
};

#endif
