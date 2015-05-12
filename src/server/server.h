
#include "../lib/mongoosecpp/MongoServer.h"
#include "../lib/mongoosecpp/MongoDispatcher.h"

#include "../game/game.h"

#ifndef _SERVER_H
#define _SERVER_H

class GameServer {
public:
	GameServer(Game* _g, int _port);
	
	bool XML_Game(Mongo::Request req, Mongo::Response resp);
	
	void run();
	
private:
	int port;
	Game* g;
	Mongo::Server server;
	Mongo::Dispatcher dispatcher;  // not to be confused with the multiple dispatchers in the Game
};

#endif
