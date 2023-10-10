CXX = g++
CXXFLAGS = -Wall

proj4:  Game.o Bloon.o Basic.o Monkey.o Dart.o Bomb.o Boomerang.o
	$(CXX) $(CXXFLAGS) proj4.cpp Game.o Bloon.o Basic.o Monkey.o Dart.o Bomb.o Boomerang.o -o proj4

Game.o: Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Basic.o: Basic.h Basic.cpp
	$(CXX) $(CXXFLAGS) -c Basic.cpp

Bloon.o: Bloon.h Bloon.cpp
	$(CXX) $(CXXFLAGS) -c Bloon.cpp

Boomerang.o: Boomerang.h Boomerang.cpp
	$(CXX) $(CXXFLAGS) -c Boomerang.cpp

Bomb.o: Bomb.h Bomb.cpp
	$(CXX) $(CXXFLAGS) -c Bomb.cpp

Dart.o: Dart.h Dart.cpp
	$(CXX) $(CXXFLAGS) -c Dart.cpp

Monkey.o: Monkey.h Monkey.cpp
	$(CXX) $(CXXFLAGS) -c Monkey.cpp

clean:
	rm *.o*

run:
	./proj4