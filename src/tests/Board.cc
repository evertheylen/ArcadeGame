#include <sstream>
#include <string>
#include "../game/board/player.h"
#include "../game/board/board.h"

class ExampleBoard: public ::testing::Test {
protected:
	friend class Board;
	
	virtual void SetUp() {
		board = new Board(10,15,"Mario vs Luigi");
		ASSERT_TRUE(board->properlyInitialized());
		(*board)(4,7) = new Player("Mario", 4, 7);
		(*board)(5,5) = new Player("Luigi", 5, 5);
	}
	
	virtual void TearDown() {
		delete(board);
	}
	
	Board* board;
};

TEST_F(ExampleBoard, Getters) {
	EXPECT_EQ(board->get_height(), 15);
	EXPECT_EQ(board->get_width(), 10);
	EXPECT_EQ(board->get_name(), "Mario vs Luigi");
}

TEST_F(ExampleBoard, Setters) {
	std::string newname = std::string("Mario vs Bowser");
	board->set_name(newname);
	EXPECT_EQ(board->get_name(), "Mario vs Bowser");
}

TEST_F(ExampleBoard, ValidLocation) {
	for (int i=0; i<10; i++) {
		for (int j=0; j<15; j++) {
			EXPECT_TRUE(board->valid_location(i,j));
		}
	}
	
	EXPECT_FALSE(board->valid_location(-4,1));
	EXPECT_FALSE(board->valid_location(4,-1));
	EXPECT_FALSE(board->valid_location(40,1));
	EXPECT_FALSE(board->valid_location(4,50));
	EXPECT_FALSE(board->valid_location(-40,-100));
	EXPECT_FALSE(board->valid_location(50,40));
}

TEST_F(ExampleBoard, GetLocation) {
	EXPECT_EQ((*board)(4,7)->get_x(), 4);
	EXPECT_EQ((*board)(4,7)->get_y(), 7);
	EXPECT_EQ((*board)(5,5)->get_x(), 5);
	EXPECT_EQ((*board)(5,5)->get_y(), 5);
	
	EXPECT_DEATH((*board)(50,4)->get_x() == 4, "");
}
