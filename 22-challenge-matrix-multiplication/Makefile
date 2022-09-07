# Matrix Multiply Challenge Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = matrixmultiply
SRC		 = matrixmultiply.cpp
LDLIBS	 = 

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)