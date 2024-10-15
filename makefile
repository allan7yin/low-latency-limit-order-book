CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = limit_order_book

SRC_DIR = .
LOB_DIR = $(SRC_DIR)/LimitOrderBook

OBJECTS = main.o \
          $(LOB_DIR)/Order.o $(LOB_DIR)/Book.o $(LOB_DIR)/Limit.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

$(LOB_DIR)/Order.o: $(LOB_DIR)/Order.cpp $(LOB_DIR)/Order.hpp
	$(CXX) $(CXXFLAGS) -c $(LOB_DIR)/Order.cpp -o $(LOB_DIR)/Order.o

$(LOB_DIR)/Book.o: $(LOB_DIR)/Book.cpp $(LOB_DIR)/Book.hpp
	$(CXX) $(CXXFLAGS) -c $(LOB_DIR)/Book.cpp -o $(LOB_DIR)/Book.o

$(LOB_DIR)/Limit.o: $(LOB_DIR)/Limit.cpp $(LOB_DIR)/Limit.hpp
	$(CXX) $(CXXFLAGS) -c $(LOB_DIR)/Limit.cpp -o $(LOB_DIR)/Limit.o

clean:
	rm -f $(OBJECTS) $(TARGET)