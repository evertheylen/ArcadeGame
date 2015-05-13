
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>



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
	dispatcher.serve("/", wrap_method(homepage));
	dispatcher.staticPages("/static","server/static");
	dispatcher.staticPages("/static/sprites","server/static/sprites"); // TODO fix?
	dispatcher.serve("/ajax", wrap_method(AJAX));
	dispatcher.servePrefix("/ajax", wrap_method(AJAX));
}

void GameServer::run() {
	std::cout << "Running!\n";
	server.start();
}

bool GameServer::AJAX(Mongo::Request req, Mongo::Response resp) {
	std::string mode = req.post("mode");
	std::stringstream resp_text;
	resp_text << "<RESPONSE>";
	std::stringstream log;
	std::string status = "OK";
	bool add_board = false;
	
	if (mode == "show") {
		resp.status(200);
		add_board = true;
	} else if (mode == "do") {
		try {
			std::string action_text = req.post("action");
			Action_parser p(&std::cout, "ajax_req");
			TiXmlDocument doc;
			doc.Parse(action_text.c_str());
			Action* a = p.parse_action(doc.RootElement(), g);
			bool success = g->do_action(a, log);
			if (!success) {
				status = "FAIL";
			}
			delete a;
		} catch (std::exception& e) {
			log << "error: " << e.what() << "\n";
			std::cout << "error: " << e.what() << "\n";
			status = "ERROR";
		}
		add_board = true;
	} else {
		std::cout << "Wrong ajax request mode: " << mode << "\n";
		resp.status(404);
	}
	
	if (add_board) {
		std::stringstream s_actions;
		g->save(resp_text, s_actions);
	}
	
	resp_text << "<LOG>\n" << log << "\n</LOG>\n";
	resp_text << "<STATUS>" << status << "</STATUS>\n";
	resp_text << "\n</RESPONSE>\n";
	resp.write(resp_text);
	
	return true;
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
