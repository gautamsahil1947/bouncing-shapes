# Makefile for SFML project

# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin

# Files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE := $(BIN_DIR)/sfml_app

# Default target
all: $(EXECUTABLE)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

# Clean generated files
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

# Run the executable
run: $(EXECUTABLE)
	$(EXECUTABLE)

.PHONY: all clean run

