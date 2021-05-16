
# Executable Name
EXENAME = wikipediawizard

# Object Types
OBJS = readFromFile.o main.o wikipediagraph.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include cs225/make/customClangEnforcement.mk

# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME) shortestpath supernodes

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

supernodes.o: src/supernodes.cpp
	$(CXX) $(CXXFLAGS) src/supernodes.cpp 

shortestpath.o: src/shortestpath.cpp 
	$(CXX) $(CXXFLAGS) src/shortestpath.cpp 

wikipediagraph.o: src/wikipediagraph.cpp src/wikipediagraph.h
	$(CXX) $(CXXFLAGS) src/wikipediagraph.cpp 

readFromFile.o: main.cpp src/readFromFile.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/readFromFile.cpp

test: output_msg catch/catchmain.cpp tests/tests.cpp src/readFromFile.cpp src/wikipediagraph.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp src/readFromFile.cpp src/wikipediagraph.cpp $(LDFLAGS) -o test

shortestpath: src/readFromFile.cpp src/wikipediagraph.cpp src/shortestpath.cpp
	$(LD) src/shortestpath.cpp src/readFromFile.cpp src/wikipediagraph.cpp $(LDFLAGS) -o shortestpath

supernodes: src/readFromFile.cpp src/wikipediagraph.cpp src/supernodes.cpp
	$(LD) src/supernodes.cpp src/readFromFile.cpp src/wikipediagraph.cpp $(LDFLAGS) -o supernodes

clean:
	-rm -f *.o $(EXENAME) test shortestpath supernodes

