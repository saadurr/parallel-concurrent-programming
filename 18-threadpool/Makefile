# Thread vs. Process Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall
TARGET	 = threadpool
SRC		 = threadpool.cpp
LDLIBS   = -lboost_system

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)