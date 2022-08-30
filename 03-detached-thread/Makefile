# Thread vs. Process Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++11
TARGET	 = detachedthread
SRC		 = detachedthread.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)