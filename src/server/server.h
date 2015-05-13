
#include "../lib/mongoosecpp/MongoServer.h"
#include "../lib/mongoosecpp/MongoDispatcher.h"

#include "../game/game.h"

#include "../actions/actions.h"

#include "../parsers/action_parser.h"

#include "../lib/tinyxml/tinyxml.h"

#ifndef _SERVER_H
#define _SERVER_H

class GameServer {
public:
	GameServer(Game* _g, int _port);
	
	bool AJAX(Mongo::Request req, Mongo::Response resp);
	bool homepage(Mongo::Request req, Mongo::Response resp);
	
	void run();
	
private:
	int port;
	Game* g;
	Mongo::Server server;
	Mongo::Dispatcher dispatcher;  // not to be confused with the multiple dispatchers in the Game
};

#endif
