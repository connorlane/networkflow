CXX=g++
CXXFLAGS = -g -std=c++11 -Wall -pedantic -DNDEBUG -Werror -Wextra
BIN=networkflow.x

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $(CXXFLAGS) $@ -c $<

clean:
	rm -f *.o
	rm -f $(BIN)

depend: .depend

.depend: $(SRC)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ > ./.depend;

include .depend
