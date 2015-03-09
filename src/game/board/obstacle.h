#include "thing.h"
#include <string>

#ifndef _Obstacle
#define _Obstacle

class Obstacle: public Thing {
public:
	Obstacle(unsigned int x, unsigned int y, int weight);
	virtual std::ostream& print(std::ostream& out);
	
	virtual char to_char();
};

#endif // _Obstacle
