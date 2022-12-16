CC=g++
CFLAGS=-Wall -Werror -Wextra -pedantic -g -std=c++2a
LDFLAGS= -lSDL2main -lSDL2

BIN=App
CSRC=$(wildcard *.cpp)
COBJ=$(CSRC:%.cpp=%.o)

all: $(BIN)

$(BIN): $(COBJ) ; $(CC) -o $@ $^ $(LDFLAGS)

.cpp.o: ; $(CC) $(CFLAGS) -c $< -o $@

clean: ; rm -f $(BIN) $(COBJ)