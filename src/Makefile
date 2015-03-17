#--- the location of the test includes; YOU MIGHT NEED TO MODIFY THESE
INCL =		../lib/gtest/include
#--- the location of the test libraries; YOU MIGHT NEED TO MODIFY THESE
TLIBPATH =	-L../lib/gtest/lib
TLIBS =		-lgtest -lgtest_main

# include all .o files in lib/tinyxml
TINYXMLLIBS = 	$(shell find ../lib/tinyxml -name '*.o')

CXXFLAGS =	-g -std=c++11 -Wall -Wextra -fstack-protector-all -I$(INCL) 

# All .cpp files not in src itself
OBJS =		$(addsuffix .o, $(basename $(shell find . -mindepth 2 -name '*.cpp')))

TARGET =	ArcadeMain ArcadeTests

#--- primary target
.PHONY: all
all: $(TARGET)


#--- compiler targets
ArcadeMain: $(OBJS) ArcadeMain.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) ArcadeMain.o $(TINYXMLLIBS)

ArcadeTests: $(OBJS) ArcadeTests.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) ArcadeTests.o $(TINYXMLLIBS) $(TLIBPATH) $(TLIBS) -pthread

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


#--- non-file targets
.PHONY: depend
depend:
	cd ../lib;\
	cd tinyxml;\
	$(CXX)  $(CXXFLAGS) -c *.cpp;\
	cd ..;\
	cd gtest;\
	rm CMakeCache.txt;\
	cmake CMakeLists.txt;\
	make;\
	mkdir lib;\
	mv libgtest.a lib/libgtest.a;\
	mv libgtest_main.a lib/libgtest_main.a;

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*~'  -delete
	#rm -f $(TARGET)
	#rm -f testOutput/file*.txt testOutput/happyDayOut.txt  testOutput/noWinnerOut.txt

.PHONY: cleann
cleann:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*~'  -delete
	rm -f $(TARGET)

	
# .PHONY: cleantests
# cleantests:
# 	rm -f testOutput/file*.txt testOutput/happyDayOut.txt

# .PHONY: depend
# depend:
# 	g++ -MM -I $(INCL) $(SRCS)

.PHONY: test
test:
	python3 tests/generate_filetests.py
	make clean
	rm -f ArcadeTests
	make ArcadeTests
	./ArcadeTests

.PHONY: echo
echo:
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo CXX = $(CXX)
	@echo LDFLAGS = $(LDFLAGS)
	@echo INCL = $(INCL)
	@echo TLIBPATH = $(TLIBPATH)
	@echo TLIBS = $(TLIBS)




