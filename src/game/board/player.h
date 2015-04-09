#include "living_thing.h"
#include "movable_thing.h"
#include "barrel.h"
#include <string>

#ifndef _Player
#define _Player

class Player: public LivingThing {
public:
	// Constants
	static const int  PLAYER_WEIGHT = 500;
	static const int  PLAYER_HEIGHT = 0;
	static const int  PLAYER_IMPORTANCE = 9001;
	static const int  PLAYER_MAXIMUM_WEIGHT = Barrel::BARREL_WEIGHT;
	
	
	//! copy constructor
	Player(const Player& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Player& operator=(const Player& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Player(std::string name = "Mario", unsigned int x = 0, unsigned int y = 0);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments for constructor of player.");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	const std::string& get_name() const;
	/**< REQUIRE(properlyInitialized(), "Player wasn't initialized when calling get_name");*/

	void set_name(const std::string& name);
	/**< REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_name");
		ENSURE(get_name() == name, "name wasn't correctly set!");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Player wasn't initialized when calling print");*/
	
	char to_char();
	/**< REQUIRE(properlyInitialized(), "Player wasn't initialized when calling to_char");*/
	
	std::string get_typename();
	
	void onEnter(MovableThing* other);
	
	void onLeave(MovableThing* other);
	
	void end_game();
	
	~Player() {}

private:
	std::string _name;
	
};

#endif // _Player
