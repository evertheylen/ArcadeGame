#include "thing.h"
#include <string>

#ifndef _Player
#define _Player

class Player: public Thing {
private:
	std::string _name;
	int _maximum_weight;

public:
	Player(std::string name = "noname", unsigned int x = 0, unsigned int y = 0);
	const std::string& get_name() const;
	void set_name(const std::string& name);
	std::ostream& print(std::ostream& out);
	
	int get_maximum_weight();
	void set_maximum_weight(int max);
	
	char to_char();
	
	~Player() {}
};

#endif // _Player
