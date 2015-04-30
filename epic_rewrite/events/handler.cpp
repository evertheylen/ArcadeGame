
#include "handler.h"

Handler::Handler(Game* _g):
		game(_g) {}

Handler::Handler() {
	game = nullptr;
}

void Handler::setGame(Game* _g) {
	game = _g;
}
