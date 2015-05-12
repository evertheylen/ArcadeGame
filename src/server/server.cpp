
#include <iostream>
#include <string>
#include <sstream>

#include "server.h"
#include "../UI/UI.h"  //split


// https://ideone.com/fV22mS

#define wrap_method(method_name) [&](Mongo::Request req, Mongo::Response resp) -> bool { return method_name(req, resp); }

GameServer::GameServer(Game* _g, int _port):
		g(_g), dispatcher(server) {
	std::cout << "started on port " << std::to_string(_port) << "\n";
	server.setOption("listening_ports", std::to_string(_port));
	/* server.setStart([&](Mongo::Request req, Mongo::Response resp) -> bool {
		// Three possible handlers:
		//   - static files (in directory static)
		//   - homepage ?
		//   - AJAX GET
		std::string path = req.getPath();
		std::vector<std::string> parts = split(path, '/');
		resp.status(200).printf(parts[0].c_str());
		resp.printf("test");
		return true;
	});
	*/
	dispatcher.staticPages("/static","server/static");
	dispatcher.serve("/game", wrap_method(XML_Game));
}

void GameServer::run() {
	std::cout << "Running!\n";
	server.start();
}

bool GameServer::XML_Game(Mongo::Request req, Mongo::Response resp) {
	resp.status(200);
	std::stringstream s_board;
	std::stringstream s_actions;
	g->save(s_board, s_actions);
	resp.write(s_board);
	
	return true;
}
