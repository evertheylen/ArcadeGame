#include <string>
#include <vector>
#include "thing.h"
#include <iostream>

#ifndef _Board
#define _Board

class Board {
public:
	Board(unsigned int width = 1, unsigned int height = 1, std::string name = std::string("No name"));
	/**< REQUIRE(width > 0 && height > 0, "incorrect height or width");
	 	ENSURE(properlyInitialized(), "constructor must end ...");*/

	~Board();

	//! copy constructor
	//! will empty the _data of this
	Board(const Board& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	//! will empty the _data of this
	Board& operator=(const Board& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	unsigned int get_height() const;
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling get_height");
		ENSURE(result > 0, "Board has incorrect height or height is not returned correctly");*/

	// void set_height(unsigned int y);

	const std::string& get_name() const;
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling get_name");*/

	void set_name(std::string& name);
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling set_name");
		 ENSURE(get_name() == name, "name not set correctly when calling set_name");*/

	unsigned int get_width() const;
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling get_width");
		ENSURE(result > 0, "Board has incorrect width or width is not returned correctly");*/

	// void set_width(unsigned int x);

	Thing*& operator()(unsigned int x, unsigned int y);
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling operator()");
	 	 REQUIRE(valid_location(x,y), "Not a valid location given to operator()"); */
	
	bool valid_location(int x, int y);
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling valid_location");*/

	friend std::ostream& operator<< (std::ostream& out, Board& board);
	/**< REQUIRE(properlyInitialized(), "Board wasn't initialized when calling operator <<");*/

	bool properlyInitialized() const;

private:
	std::string _name;
	unsigned int _width, _height;
	std::vector<std::vector<Thing*>> _data;
	Board* _initCheck;
};

#endif //_Board
