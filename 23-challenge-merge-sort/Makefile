# Merge Sort Solution Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = mergesort
SRC		 = mergesort.cpp
LDLIBS	 = 

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)