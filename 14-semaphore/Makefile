# Thread vs. Process Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = semaphore
SRC		 = semaphore.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)