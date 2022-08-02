all: main
CXXFLAGS=-Wall -g
CXX=g++
main: main.o display.o
	$(CXX) -o $@ $^
clean:
	rm -f *.o *.exe