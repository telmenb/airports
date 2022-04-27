CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++14 -g -fstandalone-debug
SRC=src/*
TEST_SRC=src/flight_graph.cpp src/heap.cpp

exec: bin/exec
tests: bin/tests

bin:
	mkdir bin

bin/exec: $(SRC)
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

bin/tests: tests/tests.cpp $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*