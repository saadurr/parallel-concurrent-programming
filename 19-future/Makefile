# Future Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = future
SRC		 = future.cpp
LDLIBS	 = 

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)