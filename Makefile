COMPILEFLAGS = -std=c++11 -Wall -Wextra -Werror
COMPILER = g++
CXXFLAGS = -Iinclude $(COMPILEFLAGS)
OPTFLAGS = -O1

COMBGRAPH = objs/CombinationGraph.o

OBJS = objs/CombinationGraph.o objs/State.o objs/Matcher.o

TESTS = test-comb-graph

all: objs tests matcher

matcher: test/GraphMatcher.cpp $(OBJS)
	$(COMPILER) $(OPTFLAGS) $(CXXFLAGS) test/GraphMatcher.cpp $(OBJS) -o graph-matcher.run

objs: $(OBJS)

tests: $(TESTS)

test-comb-graph: $(COMBGRAPH) test/TestGraph.cpp
	$(COMPILER) $(OPTFLAGS) $(CXXFLAGS) test/TestGraph.cpp $(COMBGRAPH) -o comb-graph.run

objs/CombinationGraph.o: src/CombinationGraph.cpp include/CombinationGraph.h \
												include/Graph.h
	$(COMPILER) $(OPTFLAGS) -c $< $(CXXFLAGS) -o $@

objs/State.o: src/State.cpp include/State.h
	$(COMPILER) $(OPTFLAGS) -c $< $(CXXFLAGS) -o $@

objs/Matcher.o: src/Matcher.cpp include/Matcher.h
	$(COMPILER) $(OPTFLAGS) -c $< $(CXXFLAGS) -o $@

clean:
	rm -rf objs *.run
