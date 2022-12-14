CXX = g++
CXXFLAGS = -Wall -g

program: hangman.o program.cpp
	$(CXX) $(CXXFLAGS) hangman.o program.cpp -o program
mytest: hangman.o mytest.cpp
	$(CXX) $(CXXFLAGS) hangman.o mytest.cpp -o mytest
hangman.o: hangman.cpp
	$(CXX) $(CXXFLAGS) -c hangman.cpp
val:
	valgrind ./program