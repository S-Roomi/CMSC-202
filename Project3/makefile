CXX = g++
CXXFLAGS = -Wall

proj3:  Sequencer.o Strand.o
	$(CXX) $(CXXFLAGS) proj3.cpp Sequencer.o Strand.o -o proj3

Sequencer.o: Strand.o Sequencer.cpp Sequencer.h
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

Strand.cpp: Strand.h Strand.cpp
	$(CXX) $(CXXFLAGS) -c Strand.cpp

clean:
	rm *.o*

run:
	./proj3 "proj3_data4.txt"
