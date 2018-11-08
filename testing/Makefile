CPPFLAGS=-std=c++14 -O0 # no optimizations because this is all for debugging/testing
LINKFLAGS=-I../include/

all: thread queue util
thread: thread_testing.out
queue: queue_testing.out
util: util_testing.out

%.out: %.cpp
	$(CXX) $(LINKFLAGS) $< -o $@ $(CPPFLAGS)

clean:
	rm *.out
