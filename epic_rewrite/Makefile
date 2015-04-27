
INCLUDES = -I ./entities -I ./actions -I ./events -I ./events/dispatch -I ./game -I ./UI -I ./lib/gtest/include/ -I .

CXX        = g++
CXXFLAGS   = -g3 -O0 -std=c++11 -Werror=nonnull -Werror=return-type -Werror=main -Werror=missing-include-dirs -fstack-protector-all $(INCLUDES)
#CXXFLAGS   = -O3 -std=c++14

OBJS       = $(addsuffix .o, $(basename $(shell find . -mindepth 2 -name '*.cpp' -not -path './lib/*' -and -not -path './tests/*')))
SHELL      = /bin/bash
TARGETS    = dispatch ArcadeMain ArcadeTests

# include all .o files in lib/tinyxml
TINYXMLLIBS = 	$(shell find ./lib/tinyxml -name '*.o')

# gtest stuff. I don't understand it, I don't know whether I want to understand.
#--- the location of the test includes; YOU MIGHT NEED TO MODIFY THESE
TINCL =		./lib/gtest/include
#--- the location of the test libraries; YOU MIGHT NEED TO MODIFY THESE
TLIBPATH =	-L../lib/gtest/lib
TLIBS =		-lgtest -lgtest_main


.PHONY: all
all: $(TARGETS)

.PHONY: dispatch
dispatch:
	@echo -e "\033[1;38;2;0;255;180;48;2;0;0;0m --> Creating Dispatchers \033[0m"
	@python3 ./events/dispatch/precompile.py ./events/dispatch/dispatchers.toml


ArcadeMain: $(OBJS) ArcadeMain.o
	@echo -e "\033[1;38;2;20;255;20;48;2;0;0;0m --> Compiling and linking $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(TINYXMLLIBS) ArcadeMain.o


ArcadeTests: $(OBJS) ArcadeTests.o generate_filetests
	@echo -e "\033[1;38;2;20;255;20;48;2;0;0;0m --> Compiling and linking $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS) ArcadeTests.o $(TINYXMLLIBS) $(TLIBPATH) $(TLIBS) -pthread


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

.PHONY: echo
echo:
	@echo INCLUDES = $(INCLUDES)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo OBJS = $(OBJS)

.PHONY: clean
clean:
	@find . -name '*.o' -not -path "./lib/*" -delete
	@find . -name '*.d' -not -path "./lib/*" -delete
	@find . -name '*~'  -not -path "./lib/*" -delete
	@echo -e "\033[1;38;2;250;170;0;48;2;0;0;0m --> Cleaned object files \033[0m"
	
.PHONY: cleann
cleann: clean
	@rm -f $(TARGET)
	@echo -e "\033[1;38;2;255;170;0;48;2;0;0;0m --> Cleaned executables \033[0m"
