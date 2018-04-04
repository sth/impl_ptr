
CXXFLAGS=-std=c++14 -Wall

default: main

%.o: %.cpp
	g++ ${CXXFLAGS} -I../../include -c -o $@ $<

main: example.o main.o
	g++ ${CXXFLAGS} -o main example.o main.o

clean:
	rm main *.o
