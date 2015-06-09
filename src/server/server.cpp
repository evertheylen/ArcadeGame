
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "tinyxml/tinyxml.h"
#include "../parsers/game_parser.h"

#include "server.h"
#include "../UI/UI.h"  //split

#include "../DesignByContract.h"


// ---------------------------------------------------
//
//  \          /
//   \        /
//    \  /\  /  E B S O C K E T     S E R V E R
//     \/  \/
//
// ---------------------------------------------------

void GameServer::on_open(connection_hdl hdl) {
	connections.insert(hdl);
}

void GameServer::on_close(connection_hdl hdl) {
	connections.erase(hdl);
}

void GameServer::on_message(connection_hdl hdl, SocketServer::message_ptr msg) {
	std::cout << "on_message called with hdl: " << hdl.lock().get()
	          << " and message: " << msg->get_payload()
	          << std::endl;
	
	std::string input = msg->get_payload();
	std::stringstream resp_sender;
	resp_sender << "<RESPONSE>";
	
	bool update_all = false;
	std::stringstream resp_all;
	resp_all << "<RESPONSE>";
	
	std::string status = "OK";
	if (input.length() < 5) {
		// Bad request.
		status = "ERROR";
	} else {
		std::string mode = input.substr(0,4);
		std::stringstream log;
		bool add_board = false;

		if (mode == "SHOW") {
			add_board = true;
		} else if (mode == "DOOO") {
			try {
				std::string action_text = input.substr(5);
				Action_parser p(&log, "ajax_req");
				TiXmlDocument doc;
				doc.Parse(action_text.c_str());
				if (doc.Error()) {
					status = "ERROR";
					log << "TinyXML error occured...\n";
				} else {
					Action* a = p.parse_action(doc.RootElement(), g);
					bool success = g->do_action(a, log);
					if (!success) {
						status = "FAIL";
					} else {
						add_board = true;
						update_all = true;
					}
					delete a;
				}
			} catch (ParseError& e) {
				log << "error: " << e.what() << "\n";
				std::cout << "error: " << e.what() << "\n";
				status = "ERROR";
			} catch (std::exception& e) {
				log << "error: " << e.what() << "\n";
				std::cout << "error: " << e.what() << "\n";
				status = "ERROR";
			}
			add_board = true;

			if (g->is_ended()) {
				log << "Game has ended!\n";
			}
		} else if (mode == "RSET") {
			try {
				reset();
				add_board = true;
				update_all = true;
				log << "Reset game!\n";
			} catch (std::exception& e) {
				log << "Error while resetting: " << e.what() << "\n";
				std::cout << "Error while resetting: " << e.what() << "\n";
				status = "ERROR";
			}
		} else {
			std::cout << "Wrong ajax request mode: " << mode << "\n";
			status = "ERROR";
		}
		resp_sender << "<LOG>" << log.str() << "</LOG>\n";

		if (add_board) {
			std::stringstream s_actions;
			std::stringstream s_board;
			g->save(s_board, s_actions);
			resp_sender << s_board.str();
			if (update_all) {
				resp_all << s_board.str();
			}
		}
	}
	
	if (g->is_ended()) resp_sender << "<ENDED/>\n";
	
	resp_sender << "<STATUS>" << status << "</STATUS>\n";
	resp_sender << "\n</RESPONSE>\n";
	ws_server.send(hdl, resp_sender.str(), websocketpp::frame::opcode::text);
	
	if (update_all) {
		if (g->is_ended()) resp_all << "<ENDED/>\n";
		resp_all << "\n</RESPONSE>\n";
		for (auto it: connections) {
			// Don't send to update to sender itself
			if (it.lock() != hdl.lock()) {
				try {
					ws_server.send(it, resp_all.str(), websocketpp::frame::opcode::text);
				} catch (const websocketpp::lib::error_code& e) {
					std::cout << "Echo failed because: " << e
							<< "(" << e.message() << ")" << std::endl;
				}
			}
		}
	}
}

void GameServer::ws_start() {
	// Start the server accept loop
	ws_server.start_accept();
	std::cout << "WebSockets starting...\n";
		
	// Start the ASIO io_service run loop
	try {
		ws_server.run();  // this never ends, unlike the server.start() above
	} catch (...) {
		ws_server.stop_listening();
	}
}




/*
void on_message(SocketServer* s, websocketpp::connection_hdl hdl, SocketMessage_ptr msg) {
	std::cout << "on_message called with hdl: " << hdl.lock().get()
	          << " and message: " << msg->get_payload()
	          << std::endl;

	// check for a special command to instruct the server to stop listening so
	// it can be cleanly exited.
	if (msg->get_payload() == "stop-listening") {
		s->stop_listening();
		return;
	}

	try {
		s->send(hdl, msg->get_payload(), msg->get_opcode());
	} catch (const websocketpp::lib::error_code& e) {
		std::cout << "Echo failed because: " << e
		          << "(" << e.message() << ")" << std::endl;
	}
}
*/







// ---------------------------------------------------
//
//  |     |
//  |     |
//  |-----|
//  |     |  T T P     S E R V E R
//  |     |
//                     ... and some websockets too :3
//
// ---------------------------------------------------

// https://ideone.com/fV22mS

#define wrap_method(method_name) [&](Mongo::Request req, Mongo::Response resp) -> bool { return method_name(req, resp); }

GameServer::GameServer(std::string _boardfile, std::string _actionsfile, int _port, int _ws_port):
		boardfile(_boardfile), actionsfile(_actionsfile), g(nullptr),
		port(_port), dispatcher(server),
		ws_port(_ws_port) {
	
	// Init game
	reset();
	
	// Init HTTP
	server.setOption("listening_ports", std::to_string(_port));
	
	dispatcher.serve("/", wrap_method(homepage));
	dispatcher.staticPages("/static", "server/static");
	dispatcher.staticPages("/static/sprites", "server/static/sprites"); // TODO fix?

	// Init WebSockets
	try {
		// Set logging settings
		ws_server.set_access_channels(websocketpp::log::alevel::all);
		ws_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

		// Initialize ASIO
		ws_server.init_asio();
		
		// Register our handlers
		ws_server.set_open_handler(bind(&GameServer::on_open,this,::_1));
		ws_server.set_close_handler(bind(&GameServer::on_close,this,::_1));
		ws_server.set_message_handler(bind(&GameServer::on_message,this,::_1,::_2));
		
		// Listen on the specified port (default 8081)
		ws_server.listen(ws_port);
		
	} catch (websocketpp::exception const& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "other exception" << std::endl;
	}
}

void GameServer::reset() {
	if (g != nullptr) delete g;
	
	TiXmlDocument doc_board, doc_moves;

	bool board_loaded = doc_board.LoadFile(boardfile);
	bool moves_loaded = doc_moves.LoadFile(actionsfile);

	if (!board_loaded) {
		std::cout << "Error loading board.\n";
	}

	if (!moves_loaded) {
		std::cout << "Error loading moves.\n";
	}

	if (!(board_loaded && moves_loaded)) {
		throw ParseError("Couldn't load XML files", "unspecified");
	}

	Game_parser gp(&std::cout, boardfile, actionsfile);
	g = gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
}


void GameServer::run() {
	std::cout << "Running on http://localhost:" << port << "/\n";
	server.start(); // runs in its own thread by default
	
	ws_thread = std::thread(&GameServer::ws_start, this);
}

bool GameServer::homepage(Mongo::Request req, Mongo::Response resp) {
	resp.status(200);
	resp.contentType("text/html");
	std::fstream f;
	f.open("server/static/index.html");
	resp.write(f);
	f.close();
	return true;
}


GameServer::~GameServer() {
	std::cout << "Server destructor called.\n";
	ws_server.stop_listening();
	for (auto it: connections) {
		websocketpp::close::status::value stat = websocketpp::close::status::normal;
		ws_server.close(it, stat, "Server shutting down");
	}
	ws_thread.join();
	ws_server.stop();
}
















