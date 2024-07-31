# Compiler
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

# Executable
TARGET = Demo

# Source files
SOURCES = Demo.cpp Board.cpp Player.cpp Catan.cpp ResourceType.cpp DevelopmentCardType.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJECTS)

# Run
run: $(TARGET)
	./$(TARGET)
