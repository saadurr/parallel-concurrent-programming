# Thread vs. Process Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = deadlock
SRC		 = deadlock.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)