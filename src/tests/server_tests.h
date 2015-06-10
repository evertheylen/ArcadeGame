#include "gtest/gtest.h"

#include "tinyxml/tinyxml.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "game/game.h"
#include "server/server.h"

#include <chrono>
#include <thread>

#define ms_sleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

typedef websocketpp::client<websocketpp::config::asio_client> Client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;


class FileClient {
public:
	std::ofstream file;
	Client client;
	std::thread client_thread;
	Client::connection_ptr con;
	
	FileClient(std::string uri, std::string filename) {
		client.set_access_channels(websocketpp::log::alevel::none);
		client.set_error_channels(websocketpp::log::elevel::none);
		
		file.open(filename);
		client.init_asio();
		
		client.set_message_handler(bind(&FileClient::on_message, this, ::_1, ::_2));
		
		websocketpp::lib::error_code ec;
		con = client.get_connection(uri, ec);
		client.connect(con);
		

		// Start the ASIO io_service run loop
		client_thread = std::thread(&Client::run, &this->client);
		//client.run();
	}
	
	void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
		file << msg->get_payload();
	}
	
	~FileClient() {
		file.close();
		client.reset();
		websocketpp::close::status::value stat = websocketpp::close::status::normal;
		try {
			client.close(con, stat, "Client shutting down");
		} catch (std::exception& e) {
			std::cout << "Error: " << e.what() << "\n";
		}
		client_thread.join();
	}

};

class ServerTest {
public:
	// Making these pointers so I don't have to initialize them immediatly
	GameServer* server;
	FileClient* fclient;
	
	ServerTest(std::string output_file) {
		server = new GameServer("./tests/ServerBoard.xml", "./tests/ServerActions.xml", 8080, false);
		server->run();
		ms_sleep(20);
		fclient = new FileClient("ws://localhost:8081", output_file);
		ms_sleep(20);
	}
	
	void send_to_server(std::string msg) {
		fclient->con->send(msg, websocketpp::frame::opcode::text);
		ms_sleep(20);
	}
	
	~ServerTest() {
		delete fclient;
		ms_sleep(20);
		delete server;
	}
};
