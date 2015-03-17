
#include "../game/board/player.h"
#include <sstream>

TEST(Player, EmptyInit) {
	Player p = Player();
	EXPECT_TRUE(p.properlyInitialized());
}

TEST(Player, NotProperlyInitialized) {
	char a[sizeof(Player)] {'a'};
	EXPECT_FALSE(((Player*) &a)->properlyInitialized());
}

TEST(Player, Init) {
	Player p = Player("Mario",4,8);
	EXPECT_EQ(p.get_x(), 4);
	EXPECT_EQ(p.get_y(), 8);
	EXPECT_EQ(p.get_weight(), 0);
	EXPECT_EQ(p.get_name(), "Mario");
	EXPECT_EQ(p.get_maximum_weight(), 1000);
	EXPECT_TRUE(p.properlyInitialized());
}


TEST(Player, Movable) {
	Player p = Player("Luigi",8,1);
	EXPECT_TRUE(p.is_movable());
}

TEST(Player, Print) {
	Player p = Player("Mario",8,1);
	std::stringstream ss;
	ss << p;
	EXPECT_EQ(ss.str(), "Speler Mario bevindt zich in dit speelveld op positie (8,1).");
}

TEST(Player, ToChar) {
	Player p = Player("Mario",8,1);
	EXPECT_EQ(p.to_char(), '@');
}

TEST(Player, Setters) {
	Player p = Player("Peach",50,50);
	p.set_x(4);
	p.set_y(8);
	p.set_name("Luigi");
	p.set_maximum_weight(5000);
	EXPECT_EQ(p.get_x(), 4);
	EXPECT_EQ(p.get_y(), 8);
	EXPECT_EQ(p.get_name(), "Luigi");
	EXPECT_EQ(p.get_maximum_weight(), 5000);
	EXPECT_TRUE(p.properlyInitialized());
}

TEST(Player, CopyConstructor) {
	Player pp = Player("Luigi",4,8);
	Player p = pp;
	EXPECT_EQ(p.get_x(), 4);
	EXPECT_EQ(p.get_y(), 8);
	EXPECT_EQ(p.get_name(), "Luigi");
	EXPECT_TRUE(p.properlyInitialized());
}

TEST(Player, CopyAssignment) {
	Player pp = Player("Luigi",8,12);
	Player p = Player("Mario",1,-5);
	p = pp;
	EXPECT_EQ(p.get_x(), 8);
	EXPECT_EQ(p.get_y(), 12);
	EXPECT_EQ(p.get_name(), "Luigi");
	EXPECT_TRUE(p.properlyInitialized());
}
