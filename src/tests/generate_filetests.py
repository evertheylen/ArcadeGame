#!/usr/bin/python3

import os


text = """
TEST(ArcadeGameTest{1}, {0} ) {{
	std::string Base = "tests/filetests{1}/{0}/";
	std::string board_name = Base+"Speelveld.xml";
	std::string actions_name = Base+"Acties.xml";
	
	TiXmlDocument doc_board, doc_actions;

	bool board_loaded = doc_board.LoadFile(board_name);
	bool actions_loaded = doc_actions.LoadFile(actions_name);

	ASSERT_TRUE(board_loaded && actions_loaded) << "Failed to load xml files.";
	
	std::ofstream new_cout;
	new_cout.open(Base+"output.txt"); // TODO
	
	Game_parser gp(&new_cout, board_name, actions_name);
	Game* g = gp.parse_game(doc_board.FirstChildElement(), doc_actions.FirstChildElement());
	
	//ASSERT_TRUE(g.properlyInitialized());
	
	std::ofstream output_file;
	
	output_file.open(Base+"ResterendeBewegingen_begin.txt");
	g->write_actions(output_file);
	output_file.close();
	
	g->do_all_actions(new_cout); // TODO: with new_cout
	new_cout.close();
	
	output_file.open(Base+"HuidigSpeelveld.txt");
	g->get_board()->write_board(output_file);
	output_file.close();
	
	output_file.open(Base+"ResterendeBewegingen_einde.txt");
	g->write_actions(output_file);
	output_file.close();
	
	EXPECT_TRUE(fileCompare(Base+"HuidigSpeelveld.txt", Base+"_HuidigSpeelveld.txt"));
	EXPECT_TRUE(fileCompare(Base+"ResterendeBewegingen_begin.txt", Base+"_ResterendeBewegingen_begin.txt"));
    EXPECT_TRUE(fileCompare(Base+"ResterendeBewegingen_einde.txt", Base+"_ResterendeBewegingen_einde.txt"));
	EXPECT_TRUE(fileCompare(Base+"output.txt", Base+"_output.txt"));
}}

"""

# only call from location of Makefile!
f = open('tests/filetests.tests', 'w')

for root, dirs, files in os.walk("./tests/filetests"):
    for d in dirs:
        f.write(text.format(d, ""))

for root, dirs, files in os.walk("./tests/filetests_old"):
    for d in dirs:
        f.write(text.format(d, "_old"))
