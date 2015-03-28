#ifndef _Thing
#define _Thing

#include <iostream>


class MovableThing;

class Thing {
public:
	Thing();
	/**< ENSURE(properlyInitialized(), "constructor must end...");*/

	Thing(unsigned int x, unsigned int y, int weight, int height, int importance);
	/**< ENSURE(properlyInitialized(), "constructor must end...");*/

	//! copy constructor
	Thing(const Thing& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Thing& operator=(const Thing& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	bool is_movable() const;  // _weight >= 0 (-1 means infinity)
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling is_movable");*/

	int get_weight() const;
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_weight");*/

	void set_weight(int weight);
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_weight");
		ENSURE(get_weight() == weight, "Incorrect weight specified");*/
	
	unsigned int get_x() const;
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_x");
		ENSURE(result >= 0, "Incorrect x coordinate returned");*/

	void set_x(unsigned int x);
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_x");
		ENSURE(get_x() == x && x >= 0, "Incorrect x specified");*/

	unsigned int get_y() const;
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling get_y");
		ENSURE(result >= 0, "Incorrect y coordinate returned");*/

	void set_y(unsigned int y);
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_y");
		ENSURE(get_y() == y && y >= 0, "Incorrect y specified");*/

	/* void move(unsigned int x, unsigned int y);
		REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling set_x");*/
	
	int get_height() const;
	
	virtual void onEnter(MovableThing* other);
	
	virtual void onLeave(MovableThing* other);
	
	virtual void kill();
	
	virtual bool is_alive();
	
	friend std::ostream& operator<< (std::ostream &out, Thing &thing);
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling operator <<");*/

	virtual std::ostream& print(std::ostream &out);
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling print");*/
	
	virtual char to_char();
	/**< REQUIRE(properlyInitialized(), "Thing wasn't initialized when calling to_char");*/
	
	virtual ~Thing() {}

	bool properlyInitialized () const;

protected:
	unsigned int _x, _y;
	int _weight;
	int _height;
	int _importance;  // while printing
	Thing* _initCheck;
};

#endif // _Thing
