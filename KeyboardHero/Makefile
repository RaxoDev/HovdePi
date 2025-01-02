# Compiler and flags
CXX = g++
CXXFLAGS = -I/usr/include/rtmidi -std=c++17 -Wall -Wextra

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lrtmidi

# Target executable
TARGET = KeyboardHero

# Source files
SRCS = $(wildcard *.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Rebuild the project
rebuild: clean all
