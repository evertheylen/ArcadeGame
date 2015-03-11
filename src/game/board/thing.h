#ifndef _Thing
#define _Thing

#include <iostream>

class Thing {
public:
	Thing();

	Thing(unsigned int x, unsigned int y, int weight);

	bool is_movable() const;  // _weight >= 0 (-1 means infinity)

	int get_weight() const;
	void set_weight(int weight);
	
	unsigned int get_x() const;
	void set_x(unsigned int x);

	unsigned int get_y() const;
	void set_y(unsigned int y);

	void move(unsigned int x, unsigned int y);
	friend std::ostream& operator<< (std::ostream &out, Thing &thing);
	virtual std::ostream& print(std::ostream &out);
	
	virtual char to_char();
	
	virtual ~Thing() {}

	bool properlyInitialized();

protected:
	unsigned int _x, _y;
	int _weight;
	Thing* _initCheck;

};

#endif // _Thing
