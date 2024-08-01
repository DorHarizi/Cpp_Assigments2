#!make -f

CXX=clang++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99
QTFLAGS=`pkg-config --cflags --libs Qt5Widgets`

SOURCES=treewidget.cpp Demo.cpp
HEADERS=treewidget.hpp tree.hpp node.hpp
OBJECTS=$(SOURCES:.cpp=.o)

all: demo tree

run: demo
	./$^

demo: Demo.o tree.o node.o
	$(CXX) $(CXXFLAGS) $^ -o demo

tree: treewidget.o tree.o node.o
	$(CXX) $(CXXFLAGS) $(QTFLAGS) $^ -o tree

tidy:
	clang-tidy $(SOURCES) $(HEADERS) -checks=bugprone-,clang-analyzer-,cppcoreguidelines-,performance-,portability-,readability-,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo tree
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./tree 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo tree
