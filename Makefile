CXX = g++
CXXFLAGS = -Wall `sdl-config --cflags`
LIBS = `sdl-config --libs`

all: program

program: program.cpp guilib.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

guilib.o: guilib.cpp guilib.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm *.o
	rm program
