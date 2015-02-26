#include <string>
#include <vector>
#include "thing.h"

#ifndef _Board
#define _Board

class Board {
public:
	Board(unsigned int x, unsigned int y);

	unsigned int get_height() const;

	const std::string& get_name() const;
	void set_name(std::string& name);

	unsigned int get_width() const;

	Thing* operator()(unsigned int x, unsigned int y);


private:
	std::string _name;
	unsigned int _width, _height;
	std::vector <std::vector <Thing* > > _data;
};


#endif //_Board
