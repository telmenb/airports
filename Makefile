CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++14 -g -fstandalone-debug

exec: bin/exec
tests: bin/tests

bin:
	mkdir bin

bin/exec: src/main.cpp src/flight_graph.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

bin/tests: tests/tests.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*