
#include "../game/movement/movement.h"
#include "../game/board/player.h"
#include <sstream>
#include <vector>

class ExampleMove: public ::testing::Test {
protected:
	friend class Movement;
	
	virtual void SetUp() {
		player = new Player("Mario",4,5);
		move = new Movement(Direction::up, player);
		ASSERT_TRUE(move->properlyInitialized());
	}
	
	virtual void TearDown() {
		delete(move);
		delete(player);
	}
	
	// No default constructor for game, sooo
	Movement* move;
	Player* player;
};


TEST_F(ExampleMove, NotProperlyInitialized) {
	char a[sizeof(Movement)] {'a'};
	EXPECT_FALSE(((Movement*) &a)->properlyInitialized());
}


TEST_F(ExampleMove, Init) {;
	EXPECT_EQ(move->get_dir(), Direction::up);
	EXPECT_EQ(move->get_dir_name(), "OMHOOG");
	EXPECT_EQ(move->get_player(), player);
}


TEST_F(ExampleMove, Print) {
	std::stringstream ss;
	ss << *move;
	EXPECT_EQ(ss.str(), "Speler Mario zal volgende beweging nog uitvoeren:\nOMHOOG\n");
}


TEST_F(ExampleMove, Setters) {
	move->set_dir(Direction::left);
	Player l = Player("Luigi", 5, 5);
	move->set_player(&l);
	
	EXPECT_EQ(move->get_dir(), Direction::left);
	EXPECT_EQ(move->get_dir_name(), "LINKS");
	EXPECT_EQ(move->get_player(), &l);
}


TEST_F(ExampleMove, CopyConstructor) {
	Player l = Player("Luigi", 5, 5);
	Movement m = *move;
	EXPECT_EQ(m.get_dir(), Direction::up);
	EXPECT_EQ(m.get_dir_name(), "OMHOOG");
	EXPECT_EQ(m.get_player(), player);
}


TEST_F(ExampleMove, CopyAssignment) {
	Player l = Player("Luigi", 5, 5);
	Movement m = Movement(Direction::down, &l);
	m = *move;
	EXPECT_EQ(m.get_dir(), Direction::up);
	EXPECT_EQ(m.get_dir_name(), "OMHOOG");
	EXPECT_EQ(m.get_player(), player);
}


// Direction

TEST(Direction, toDirection) {
	EXPECT_EQ(toDirection("OMHOOG"), Direction::up);
	EXPECT_EQ(toDirection("OMLAAG"), Direction::down);
	EXPECT_EQ(toDirection("LINKS"), Direction::left);
	EXPECT_EQ(toDirection("RECHTS"), Direction::right);
	EXPECT_EQ(toDirection("OMHOOOG"), Direction::no_dir);
	EXPECT_EQ(toDirection(""), Direction::no_dir);
}

TEST(Direction, doDirection) {
	std::vector<Direction> v = {Direction::up, Direction::down, Direction::left, Direction::right};
	for (auto i: v) {
		unsigned int x = 5;
		unsigned int y = 4;
		doDirection(i, x, y);
		doReverseDirection(i, x, y);
		EXPECT_EQ(x,5);
		EXPECT_EQ(y,4);
	}
}

