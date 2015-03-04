#include <string>
#include "../board/player.h"

#ifndef _Movement
#define _Movement

enum Direction {up, left, down, right};

class Movement {
public:
	Movement(Direction dir, Player* player);
	Movement(std::string dir_s, Player* player);

	Direction get_dir() const;
	void set_dir(Direction dir);

	const Player* get_player() const;

	// When setting to other player, take care of memory leaks.
	void set_player(Player* player);

private:
	Direction _dir;
	Player* _player;
};


#endif // _Movement
