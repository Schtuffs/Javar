CXX		 = g++

EXE		 = javar

SRC		 = ../src
INCLUDE	 = ../include
LIB		 = ../lib

FLAGS	 = -std=c++20 -I$(INCLUDE) -L$(LIB)
CXXFLAGS = -c -Wall $(FLAGS)
LDFLAGS	 = $(FLAGS) -o

OBJECTS	 = main.o MvnGenerator.o MvnRunner.o

all: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(EXE)

main.o: $(SRC)/main.cpp MvnGenerator.o MvnRunner.o
	$(CXX) $(CXXFLAGS) $<

MvnGenerator.o: $(SRC)/MvnGenerator.cpp $(INCLUDE)/MvnGenerator.h
	$(CXX) $(CXXFLAGS) $<

MvnRunner.o: $(SRC)/MvnRunner.cpp $(INCLUDE)/MvnRunner.h
	$(CXX) $(CXXFLAGS) $<

clean:
	del -q *.exe *.o
