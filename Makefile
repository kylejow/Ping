all: main
CXXFLAGS=-Wall -g
CXX=g++
main: main.o
	$(CXX) -o $@ $^
clean:
	rm -f *.o *.exe