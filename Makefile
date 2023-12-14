# Specify the target binary
TARGET = project

# Specify the C++ compiler
CXX = g++

# Specify the C++ compiler flags
CXXFLAGS = -Wall -std=c++17

# Specify the source files
SOURCES = $(wildcard *.cpp)

# Specify the object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default make target
all: $(TARGET)

# Link the object files to create the target binary
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile the source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)
