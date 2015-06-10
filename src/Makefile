
INCLUDES = -L./lib/boost/stage/lib -I ./entities -I ./actions -I ./events -I ./events/dispatch -I ./game -I ./UI -I ./lib/gtest/include/ -I ./lib/mongoosecpp/ -I . -I ./lib/ -I ./lib/websocketpp/ -I ./lib/boost

CXX        = g++
CXXFLAGS   = -g3 -O0 -std=c++11 -Werror=nonnull -Werror=return-type -Werror=main -fstack-protector-all $(INCLUDES)
#CXXFLAGS   = -O3 -std=c++11 -fstack-protector-all $(INCLUDES)

OBJS       = $(addsuffix .o, $(basename $(shell find . -mindepth 2 \( -name '*.cpp' -or -name '*.c' \) -and -not -path './lib/gtest/*' -and -not -path './lib/tinyxml/*' -and -not -path './tests/*' -and -not -path './lib/boost/*')))
SHELL      = /bin/bash
TARGETS    = ArcadeMain ArcadeTests

# include all .o files in lib/tinyxml
TINYXMLLIBS = 	$(shell find ./lib/tinyxml -name '*.o')


#--- the location of the test includes; YOU MIGHT NEED TO MODIFY THESE
TINCL =		./lib/gtest/include
#--- the location of the test libraries; YOU MIGHT NEED TO MODIFY THESE
TLIBPATH =	-L./lib/gtest/lib
TLIBS =		-lgtest -lgtest_main

# last 4 are for Websockets
LIBS = -ldl -lpthread -lreadline -lrt -Wl,-Bstatic -lboost_system -lboost_timer -lboost_chrono -Wl,-Bdynamic


.PHONY: all
all: $(TARGETS)

.PHONY: dispatch
dispatch:
	@echo -e "\033[1;38;2;0;255;180;48;2;0;0;0m --> Creating Dispatchers \033[0m"
	@python3 ./events/dispatch/precompile.py ./events/dispatch/dispatchers.toml


ArcadeMain: $(OBJS) ArcadeMain.o
	@echo -e "\033[1;38;2;20;255;20;48;2;0;0;0m --> Compiling and linking $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(TINYXMLLIBS) ArcadeMain.o $(LIBS)

test: $(OBJS) test.o
	@echo -e "\033[1;38;2;20;255;20;48;2;0;0;0m --> Compiling and linking $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(TINYXMLLIBS) test.o $(LIBS)

ArcadeTests: $(OBJS) generate_filetests ArcadeTests.o
	@echo -e "\033[1;38;2;20;255;20;48;2;0;0;0m --> Compiling and linking $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS) ArcadeTests.o $(TINYXMLLIBS) $(TLIBPATH) $(TLIBS) -pthread $(LIBS)


.PHONY: generate_filetests
generate_filetests:
	python3 ./tests/generate_filetests.py


%.o: %.cpp %.h
	@echo -e "\033[1;38;2;0;255;255;48;2;0;0;0m --> Compiling $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: depend
depend:
	@echo -e "\033[1;38;2;0;255;180;48;2;0;0;0m --> Making depencies \033[0m"
	cd lib;\
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
	cd lib/boost/;\
	./bootstrap.sh --with-libraries=system,chrono,timer;\
	./b2;	

.PHONY: echo
echo:
	@echo INCLUDES = $(INCLUDES)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo OBJS = $(OBJS)

.PHONY: clean
clean:
	@find . -name '*.o' -not -path './lib/gtest/*' -and -not -path './lib/tinyxml/*' -delete
	@find . -name '*.d' -not -path './lib/gtest/*' -and -not -path './lib/tinyxml/*' -delete
	@find . -name '*~'  -not -path './lib/gtest/*' -and -not -path './lib/tinyxml/*' -delete
	@echo -e "\033[1;38;2;250;170;0;48;2;0;0;0m --> Cleaned object files \033[0m"
	
.PHONY: cleann
cleann: clean
	@rm -f $(TARGET)
	@echo -e "\033[1;38;2;255;170;0;48;2;0;0;0m --> Cleaned executables \033[0m"
