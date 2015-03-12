
import os

# only call from src!
f = open('tests/filetests.tests', 'w')

text = """
TEST_F(ArcadeGameTest, {0} ) {{
	#define Base std::string("tests/filetests/{0}/")

	TiXmlDocument doc_board, doc_moves;

	bool board_loaded = doc_board.LoadFile((Base + "Speelveld.xml").c_str());
	bool moves_loaded = doc_moves.LoadFile((Base + "Bewegingen.xml").c_str());

	EXPECT_TRUE(board_loaded && moves_loaded) << "Failed to load xml files.";
	
	Game g = Game(doc_board, doc_moves);
	
	std::ofstream output_file;
	
	output_file.open(Base+"ResterendeBewegingen_begin.txt");
	g.writeMovements(output_file);
	output_file.close();
	
	output_file.open(Base+"output.txt");
	g.doAllMoves(output_file);
	output_file.close();
	
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
}}

"""

for root, dirs, files in os.walk("./tests/filetests"):
    for d in dirs:
        f.write(text.format(d))
