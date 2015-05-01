#include <iostream>
#include <functional>

#include "game/game.h"
#include "parsers/game_parser.h"
#include "UI/UI.h"

#include "lib/tinyxml/tinyxml.h"

int main(int argc, const char** argv) {
	if (argc == 2) {
		UI user_interface;
		std::string arg(argv[1]);
		for (auto s: split(arg, ';')) {
			std::cout << "\033[1;38;2;255;0;0;48;2;0;0;0m> " << s << "\033\[m\n";
			user_interface.fancy_command(s);
		}
	} else {
		UI user_interface;
		user_interface.run();
	}
}


/*
 * TODO
 *  - Events based framework
 *  - Components
 *
 */
