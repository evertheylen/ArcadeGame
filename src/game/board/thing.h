#ifndef _Thing
#define _Thing

class Thing {
public:
	Thing();

	Thing(unsigned int x, unsigned int y, bool movable);

	bool is_movable() const;
	void set_movable(bool movable);

	unsigned int get_x() const;
	void set_x(unsigned int x);

	unsigned int get_y() const;
	void set_y(unsigned int y);

	void move(unsigned int x, unsigned int y);

protected:
	unsigned int _x, _y;
	bool _movable;


};

#endif // _Thing
