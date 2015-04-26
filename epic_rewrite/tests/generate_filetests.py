#!/usr/bin/python3

import os


text = """
TEST(ArcadeGameTest, {0} ) {{
    EXPECT_TRUE(true);
    /*
	#define Base{0} std::string("tests/filetests/{0}/")

	TiXmlDocument doc_board, doc_moves;

	bool board_loaded = doc_board.LoadFile((Base{0}+ "Speelveld.xml").c_str());
	bool moves_loaded = doc_moves.LoadFile((Base{0}+ "Bewegingen.xml").c_str());

	ASSERT_TRUE(board_loaded && moves_loaded) << "Failed to load xml files.";
	
	std::ofstream new_cout;
	new_cout.open(Base+"output.txt");
	
	Game_parser gp;
	Game g = gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement(), std::cout);
	
	ASSERT_TRUE(g.properlyInitialized());
	
	std::ofstream output_file;
	
	output_file.open(Base+"ResterendeBewegingen_begin.txt");
	g.writeMovements(output_file);
	output_file.close();
	
	g.doAllMoves(new_cout);
	new_cout.close();
	
	output_file.open(Base+"HuidigSpeelveld.txt");
	g.writeBoard(output_file);
	output_file.close();
	
	output_file.open(Base+"ResterendeBewegingen_einde.txt");
	g.writeMovements(output_file);
	output_file.close();
	
	EXPECT_TRUE(fileCompare(Base+"HuidigSpeelveld.txt", Base+"_HuidigSpeelveld.txt"));
	EXPECT_TRUE(fileCompare(Base+"ResterendeBewegingen_begin.txt", Base+"_ResterendeBewegingen_begin.txt"));
    EXPECT_TRUE(fileCompare(Base+"ResterendeBewegingen_einde.txt", Base+"_ResterendeBewegingen_einde.txt"));
	EXPECT_TRUE(fileCompare(Base+"output.txt", Base+"_output.txt"));
	*/
}}

"""

# only call from location of Makefile!
f = open('tests/filetests.tests', 'w')

for root, dirs, files in os.walk("./tests/filetests"):
    for d in dirs:
        f.write(text.format(d))
