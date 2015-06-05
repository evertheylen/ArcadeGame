#ifndef _SERVER_H
#define _SERVER_H

#include <set>

#include "../lib/mongoosecpp/MongoServer.h"
#include "../lib/mongoosecpp/MongoDispatcher.h"

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
typedef websocketpp::server<websocketpp::config::asio> SocketServer;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef SocketServer::message_ptr SocketMessage_ptr;

#include "../game/game.h"

#include "../actions/actions.h"

#include "../parsers/action_parser.h"



class GameServer {
public:
	GameServer(Game* _g, int _port, int _ws_port=8081);
	
	// ------ HTTP ------
	bool AJAX(Mongo::Request req, Mongo::Response resp);
	bool homepage(Mongo::Request req, Mongo::Response resp);
	
	void run();
	
	// ------ Websockets ------
	void on_open(connection_hdl hdl);
	
	void on_close(connection_hdl hdl);
	
	void on_message(connection_hdl hdl, SocketServer::message_ptr msg);
	
	void update_board();
	
	
private:
	// ------ HTTP ------
	int port;
	Game* g;
	Mongo::Server server;
	Mongo::Dispatcher dispatcher;  // not to be confused with the 'multiple dispatchers' in Game
	
	// ------ Websockets ------
	typedef std::set<connection_hdl,std::owner_less<connection_hdl>> con_list;
	int ws_port;
	SocketServer ws_server;
	con_list connections;
};

#endif
