#include <string>
#include "../board/player.h"

#ifndef _Movement
#define _Movement

enum Direction {up, left, down, right};

void doDirection(Direction dir, unsigned int& x, unsigned int& y);
void doReverseDirection(Direction dir, unsigned int& x, unsigned int& y);

class Movement {
public:
	Movement(Direction dir, Player* player);
	Movement(std::string dir_s, Player* player);

	Direction get_dir() const;
	std::string get_dir_name() const;
	void set_dir(Direction dir);

	Player* get_player() const;

	// When setting to other player, take care of memory leaks.
	void set_player(Player* player);

	friend std::ostream& operator<< (std::ostream &out, Movement& move);

	bool properlyInitialized();

private:
	Direction _dir;
	Player* _player;
	Movement* _initCheck;
};


#endif // _Movement
