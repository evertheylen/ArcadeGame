#include "thing.h"
#include <string>

#ifndef _Player
#define _Player

class Player: public Thing {
public:
	// copy constructor
	Player(const Player& that);
	// ENSURE(properlyInitialized(), "Copy constructor must end...");

	// copy assignment
	Player& operator=(const Player& that);
	// ENSURE(properlyInitialized(), "Copy by assignment must end...");

	Player(std::string name = "noname", unsigned int x = 0, unsigned int y = 0);
	// REQUIRE(x >= 0 && y >= 0, "Incorrect arguments for constructor of player.");
	// ENSURE(properlyInitialized(), "constructor must end...");

	const std::string& get_name() const;
	// REQUIRE(properlyInitialized(), "Player wasn't initialized when calling get_name");

	void set_name(const std::string& name);
	// REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_name");
	// ENSURE(get_name() == name && name != "", "If you name your player "" you will get in trouble mate");

	std::ostream& print(std::ostream& out);
	// REQUIRE(properlyInitialized(), "Player wasn't initialized when calling print");
	
	int get_maximum_weight();
	// REQUIRE(properlyInitialized(), "Player wasn't initialized when calling get_maximum_weight");

	void set_maximum_weight(int max);
	// REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_maximum_weight");
	// ENSURE(get_maximum_weight() == max, "Maximum_weight wasn't correctly set!");
	
	char to_char();
	// REQUIRE(properlyInitialized(), "Player wasn't initialized when calling to_char");
	
	~Player() {}

private:
	std::string _name;
	int _maximum_weight;

};

#endif // _Player
