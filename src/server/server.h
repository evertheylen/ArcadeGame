#ifndef _SERVER_H
#define _SERVER_H

#include <set>

#include "../lib/mongoosecpp/MongoServer.h"
#include "../lib/mongoosecpp/MongoDispatcher.h"

#define WEBSOCKETPP_STRICT_MASKING
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

struct game_config: public websocketpp::config::asio {
	// pull default settings from our core config
	typedef websocketpp::config::asio core;

	typedef core::concurrency_type concurrency_type;
	typedef core::request_type request_type;
	typedef core::response_type response_type;
	typedef core::message_type message_type;
	typedef core::con_msg_manager_type con_msg_manager_type;
	typedef core::endpoint_msg_manager_type endpoint_msg_manager_type;

	typedef core::alog_type alog_type;
	typedef core::elog_type elog_type;
	typedef core::rng_type rng_type;
	typedef core::endpoint_base endpoint_base;

	static bool const enable_multithreading = true;

	struct transport_config : public core::transport_config {
		typedef core::concurrency_type concurrency_type;
		typedef core::elog_type elog_type;
		typedef core::alog_type alog_type;
		typedef core::request_type request_type;
		typedef core::response_type response_type;

		static bool const enable_multithreading = true;
	};

	typedef websocketpp::transport::asio::endpoint<transport_config>
	transport_type;

	static const websocketpp::log::level elog_level =
	    websocketpp::log::elevel::all;
	static const websocketpp::log::level alog_level =
	    websocketpp::log::alevel::all;
};

typedef websocketpp::server<game_config> SocketServer;

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
	GameServer(std::string _boardfile, std::string _actionsfile, int _port, int _ws_port=8081);
	
	void reset();
	
	~GameServer();
	
	// ------ HTTP ------
	bool homepage(Mongo::Request req, Mongo::Response resp);
	
	void run();
	
	// ------ Websockets ------
	void on_open(connection_hdl hdl);
	
	void on_close(connection_hdl hdl);
	
	void on_message(connection_hdl hdl, SocketServer::message_ptr msg);
	
	
	
private:
	Game* g;
	std::string boardfile;
	std::string actionsfile;
	
	// ------ HTTP ------
	int port;
	Mongo::Server server;
	Mongo::Dispatcher dispatcher;  // not to be confused with the 'multiple dispatchers' in Game
	
	// ------ Websockets ------
	typedef std::set<connection_hdl,std::owner_less<connection_hdl>> con_list;
	int ws_port;
	SocketServer ws_server;
	con_list connections;
};

#endif
