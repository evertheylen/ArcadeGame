
INCLUDES = $(shell find . -type d -exec echo "-I {}" \;)

CXXFLAGS   = -g3 -O0 -std=c++11 -Werror=nonnull -Werror=return-type -Werror=main -Werror=missing-include-dirs -fstack-protector-all $(INCLUDES)  $(shell find . -type d -exec echo "-I {}" \;)
#CXXFLAGS   = -O3 -std=c++14

OBJS       = $(addsuffix .o, $(basename $(shell find . -mindepth 2 -name '*.cpp')))
SHELL      = /bin/bash
TARGETS    = ArcadeMain ArcadeTests

.PHONY: all
all: $(TARGETS)

ArcadeMain: $(OBJS) ArcadeMain.o
	@echo -e "\033[1;38;2;20;255;20;48;2;0;0;0m --> Compiling and linking $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS) ArcadeMain.o $(TINYXMLLIBS)

# TODO ArcadeTests

%.o: %.cpp %.h
	@echo -e "\033[1;38;2;0;255;255;48;2;0;0;0m --> Compiling $@ \033[0m"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

	
.PHONY: echo
echo:
	@echo INCLUDES = $(INCLUDES)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo OBJS = $(OBJS)

.PHONY: clean
clean:
	@find . -name '*.o' -delete
	@find . -name '*.d' -delete
	@find . -name '*~'  -delete
	@echo -e "\033[1;38;2;250;170;0;48;2;0;0;0m --> Cleaned object files \033[0m"
	
.PHONY: cleann
cleann:
	@find . -name '*.o' -delete
	@find . -name '*.d' -delete
	@find . -name '*~'  -delete
	@rm -f $(TARGET)
	@echo -e "\033[1;38;2;255;170;0;48;2;0;0;0m --> Cleaned object files and executables \033[0m"
