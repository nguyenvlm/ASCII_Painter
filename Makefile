# DEFAULT C++ MAKEFILE BY NGUYENVLM

PROJECT_NAME = ASCII_Painter

CXX = g++
CFLAGS = -std=c++14 -Wall -O2 -static-libgcc -static-libstdc++
LFLAGS = -s 

BIN = $(patsubst %, bin/%.exe, $(PROJECT_NAME))

SRC = $(wildcard *.cpp)
DEP = $(wildcard *.h) $(wildcard *.hpp)
OBJ = $(patsubst %.cpp, obj/%.o, $(SRC))

obj/%.o: %.cpp $(DEP)
	$(CXX) $(CFLAGS) $(LFLAGS) -o $@ -c $<

$(BIN): $(OBJ) $(DEP)
	$(CXX) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(BIN)

clean:
	-rm $(OBJ)

.PHONY: clean