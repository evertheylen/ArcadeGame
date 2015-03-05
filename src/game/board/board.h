#include <string>
#include <vector>
#include "thing.h"

#ifndef _Board
#define _Board

class Board {
public:
	Board(unsigned int x = 0, unsigned int y = 0);

	~Board();

	unsigned int get_height() const;
	//void set_height(unsigned int y);

	const std::string& get_name() const;
	void set_name(std::string& name);

	unsigned int get_width() const;
	//void set_width(unsigned int x);

	Thing*& operator()(unsigned int x, unsigned int y);

private:
	std::string _name;
	unsigned int _width, _height;
	std::vector<std::vector<Thing*>> _data;
};

#endif //_Board
