
#include "server_tests.h"

#include <cstdlib>

TEST(Server, HappyDay) {
	{ServerTest s("./tests/server/HappyDay");
	s.send_to_server("SHOW:blabla");}
	
	EXPECT_TRUE(fileCompare("./tests/server/HappyDay", "./tests/server/_HappyDay"));
}

TEST(Server, Show) {
	{ServerTest s("./tests/server/Show");
	s.send_to_server("SHOW:");}
	
	EXPECT_TRUE(fileCompare("./tests/server/Show", "./tests/server/_Show"));
}

TEST(Server, TooShort) {
	{ServerTest s("./tests/server/TooShort");
	s.send_to_server("SHO");}
	
	EXPECT_TRUE(fileCompare("./tests/server/TooShort", "./tests/server/_TooShort"));
}

TEST(Server, Empty) {
	{ServerTest s("./tests/server/Empty");
	s.send_to_server("");}
	
	EXPECT_TRUE(fileCompare("./tests/server/Empty", "./tests/server/_Empty"));
}

TEST(Server, GoUp) {
	{ServerTest s("./tests/server/GoUp");
	s.send_to_server("DOOO:<BEWEGING><ID>Chip</ID><RICHTING>OMHOOG</RICHTING></BEWEGING>");}
	
	EXPECT_TRUE(fileCompare("./tests/server/GoUp", "./tests/server/_GoUp"));
}

TEST(Server, GoUpAndKill) {
	{ServerTest s("./tests/server/GoUpAndKill");
	s.send_to_server("DOOO:<BEWEGING><ID>Chip</ID><RICHTING>OMHOOG</RICHTING></BEWEGING>");
	s.send_to_server("DOOO:<AANVAL><ID>Chip</ID><RICHTING>LINKS</RICHTING></AANVAL>");}
	
	EXPECT_TRUE(fileCompare("./tests/server/GoUpAndKill", "./tests/server/_GoUpAndKill"));
}

TEST(Server, Reset) {
	{ServerTest s("./tests/server/Reset");
	s.send_to_server("RSET:");}
	
	EXPECT_TRUE(fileCompare("./tests/server/Reset", "./tests/server/_Reset"));
}


// For tests of the websocket framework itself: (really extensively tested)
//   http://autobahn.websocketpp.org/servers/
