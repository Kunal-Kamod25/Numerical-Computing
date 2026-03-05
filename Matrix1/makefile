CC=g++
CFLAGS=-std=c++17 -Wall -I.

DEPS=LU.hpp

TARGET=final_output

OBJS=LU.o Main_LU.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o final_outp