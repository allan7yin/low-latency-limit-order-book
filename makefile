# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = my_program

# Directories
SRC_DIR = .
LOB_DIR = $(SRC_DIR)/LimitOrderBook
RBT_DIR = $(SRC_DIR)/RedBlackTree

# Object files
OBJECTS = main.o \
          $(LOB_DIR)/Order.o $(LOB_DIR)/Book.o $(LOB_DIR)/Limit.o \
          $(RBT_DIR)/RedBlackTree.o $(RBT_DIR)/RedBlackTreeNode.o

# Default target
all: $(TARGET)

# Rule for building the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile main.cc
main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

# Compile LimitOrderBook objects
$(LOB_DIR)/Order.o: $(LOB_DIR)/Order.cpp $(LOB_DIR)/Order.hpp
	$(CXX) $(CXXFLAGS) -c $(LOB_DIR)/Order.cpp -o $(LOB_DIR)/Order.o

$(LOB_DIR)/Book.o: $(LOB_DIR)/Book.cpp $(LOB_DIR)/Book.hpp
	$(CXX) $(CXXFLAGS) -c $(LOB_DIR)/Book.cpp -o $(LOB_DIR)/Book.o

$(LOB_DIR)/Limit.o: $(LOB_DIR)/Limit.cpp $(LOB_DIR)/Limit.hpp
	$(CXX) $(CXXFLAGS) -c $(LOB_DIR)/Limit.cpp -o $(LOB_DIR)/Limit.o

# Compile RedBlackTree objects
$(RBT_DIR)/RedBlackTree.o: $(RBT_DIR)/RedBlackTree.cpp $(RBT_DIR)/RedBlackTree.hpp
	$(CXX) $(CXXFLAGS) -c $(RBT_DIR)/RedBlackTree.cpp -o $(RBT_DIR)/RedBlackTree.o

$(RBT_DIR)/RedBlackTreeNode.o: $(RBT_DIR)/RedBlackTreeNode.cpp $(RBT_DIR)/RedBlackTreeNode.hpp
	$(CXX) $(CXXFLAGS) -c $(RBT_DIR)/RedBlackTreeNode.cpp -o $(RBT_DIR)/RedBlackTreeNode.o

# Clean up object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)