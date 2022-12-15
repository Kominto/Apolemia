CC=g++
CFLAGS=-Wall -Werror -Wextra -pedantic -g -std=c++2a
LDFLAGS=

BIN=App
CSRC=$(wildcard *.cpp)
COBJ=$(CSRC:%.cpp=%.o)

all: $(BIN)

$(BIN): $(COBJ) ; $(CC) $(LDFLAGS) -o $@ $^

.cpp.o: ; $(CC) $(CFLAGS) -c $< -o $@

clean: ; rm -f $(BIN) $(COBJ)