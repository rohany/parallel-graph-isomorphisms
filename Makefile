COMPILEFLAGS = -std=c++11 -Wall -Wextra -Werror
COMPILER = g++
CXXFLAGS = -Iinclude $(COMPILEFLAGS)
OPTFLAGS = -O1

ADJMATRIX = objs/AdjacencyMatrix.o

OBJS = objs/AdjacencyMatrix.o objs/State.o objs/Matcher.o

TESTS = test-adj-matrix

all: objs tests matcher

matcher: test/GraphMatcher.cpp $(OBJS)
	$(COMPILER) $(OPTFLAGS) $(CXXFLAGS) test/GraphMatcher.cpp $(OBJS) -o graph-matcher.run

objs: $(OBJS)

tests: $(TESTS)

test-adj-matrix: $(ADJMATRIX) test/TestGraph.cpp
	$(COMPILER) $(OPTFLAGS) $(CXXFLAGS) test/TestGraph.cpp $(ADJMATRIX) -o adj-matrix-test.run

objs/AdjacencyMatrix.o: src/AdjacencyMatrix.cpp include/AdjacencyMatrix.h \
												include/Graph.h
	$(COMPILER) $(OPTFLAGS) -c $< $(CXXFLAGS) -o $@

objs/State.o: src/State.cpp include/State.h
	$(COMPILER) $(OPTFLAGS) -c $< $(CXXFLAGS) -o $@

objs/Matcher.o: src/Matcher.cpp include/Matcher.h
	$(COMPILER) $(OPTFLAGS) -c $< $(CXXFLAGS) -o $@

clean:
	rm -rf objs *.run
