#include "thing.h"
#include <string>

#ifndef _Player
#define _Player

class Player: public Thing {
private:
	std::string _name;

public:
	Player(std::string name, unsigned int x = 0, unsigned int y = 0);
	const std::string& get_name() const;
	void set_name(const std::string& name);
};

#endif // _Player
