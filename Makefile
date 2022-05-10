CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++17 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests


clean:
	rm -f bin/*
	
bin/exec: src/main.cc src/graph.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: tests/tests.cc src/graph.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean tests
