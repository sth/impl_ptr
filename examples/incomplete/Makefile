
CXXFLAGS=-std=c++14 -Wall

default: example

%.o: %.cpp
	g++ ${CXXFLAGS} -I../../include -c -o $@ $<

example: example.o main.o
	g++ ${CXXFLAGS} -o example example.o main.o

clean:
	rm example *.o
