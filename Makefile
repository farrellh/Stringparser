
CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: stringparser


stringparser: stackstr.o lliststr.o stringparser.cpp
	$(CXX)  $(CPPFLAGS) $^ -o $@

stackstr.o: stackstr.cpp stackstr.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

lliststr.o: lliststr.cpp lliststr.h 
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f stringparser
	rm -f stackstr.o
	rm -f lliststr.o