# Compiler
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Iinclude

# Executables
TARGET = Demo
TEST_TARGET = test_catan

# Source files
SOURCES = Demo.cpp Board.cpp Player.cpp Catan.cpp ResourceType.cpp DevelopmentCardType.cpp

# Test source files
TEST_SOURCES = test_catan.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default rule
all: $(TARGET) $(TEST_TARGET)

# Link main target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Link test target
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)

# Run
run: $(TARGET)
	./$(TARGET)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)
