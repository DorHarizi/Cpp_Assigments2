CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion

SOURCES = Demo.cpp
HEADERS = tree.hpp node.hpp
OBJECTS = $(SOURCES:.cpp=.o)

all: demo

demo: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o demo

run: demo
	./demo

valgrind: demo
	valgrind --tool=memcheck -v --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./demo

clean:
	rm -f $(OBJECTS) demo
