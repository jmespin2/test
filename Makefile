EXENAME = maze_solver
OBJS = main.o maze.o point.o node.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp maze.h
	$(CXX) $(CXXFLAGS) main.cpp

maze.o : maze.cpp maze.h
	$(CXX) $(CXXFLAGS) maze.cpp

point.o : point.cpp point.h
	$(CXX) $(CXXFLAGS) point.cpp
node.o : node.cpp node.h
	$(CXX) $(CXXFLAGS) node.cpp

clean :
	-rm -f *.o $(EXENAME)
