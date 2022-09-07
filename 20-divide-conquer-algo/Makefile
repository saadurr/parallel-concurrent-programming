# Divide and Conquer Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = divideconquer
SRC		 = divideconquer.cpp
LDLIBS	 = 

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)