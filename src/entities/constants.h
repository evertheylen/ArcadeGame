
#ifndef _H_Constants
#define _H_Constants

/*
props = [["int", "height"], ["int","weight"], ["char", "symbol"]]
ents = ["Barrel","Goal","Wall","Actor","Player","Monster","Water","Boobytrap","Button","Gate"]
for e in ents:
    print("//", e)
    for p in props:
        print("\tconst {} ".format(p[0]) + "{}_{} = ".format(e, p[1]).upper())
    print("")

*/

// Barrel
	const int BARREL_HEIGHT = 100;
	const int BARREL_WEIGHT = 1000;
	const char BARREL_SYMBOL = 'O';

// Goal
	const char GOAL_SYMBOL = 'X'; 

// Wall
	const int WALL_HEIGHT = 200;
	const int WALL_WEIGHT = 10000;
	const char WALL_SYMBOL = '#';

// Actor
	const int ACTOR_HEIGHT = 0;
	const int ACTOR_WEIGHT = 100;
	const int ACTOR_LIVES = 1;
	const int ACTOR_POWER = 1500;  // 1 barrel, 5 actors

	// Player
		const char PLAYER_SYMBOL = 'Y';

	// Monster
		const char MONSTER_SYMBOL = '@';


// Water
	const int WATER_HEIGHT = -100;
	const int WATER_WEIGHT = 500;
	const char WATER_SYMBOL_EMPTY = '~';
	const char WATER_SYMBOL_FULL = ' ';

// Boobytrap
	const int BOOBYTRAP_LIVES = 1;
	const char BOOBYTRAP_SYMBOL = 0;

// Button
	const char BUTTON_SYMBOL = '.';
	// Events
		const int BUTTON_ACTIVATE_FROM = 999;  // more than water!

// Gate
	const int GATE_HEIGHT_OPEN = 0;
	const int GATE_HEIGHT_CLOSED = 100;
	const int GATE_WEIGHT = 500;
	const char GATE_SYMBOL_OPEN = 0;
	const char GATE_SYMBOL_CLOSED = '=';



#endif