CPPFLAGS=-std=c++14 -O0 # no optimizations because this is all for debugging/testing
LINKFLAGS=-I../include/

all: thread util string io
thread: thread_testing.out
util: util_testing.out
string: string_testing.out
io: io_testing.out

%.out: %.cpp
	$(CXX) $(LINKFLAGS) $< -o $@ $(CPPFLAGS)

clean:
	rm *.out
