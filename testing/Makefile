CPPFLAGS=-std=c++14 -O0
LINKFLAGS=-I../include/

all: thread queue
thread: thread_testing.out
queue: queue_testing.out

thread_testing.out: thread_testing.cpp
	g++ $(LINKFLAGS) $< -o $@ $(CPPFLAGS)

queue_testing.out: queue_testing.cpp
	g++ $(LINKFLAGS) $< -o $@ $(CPPFLAGS)

clean:
	rm *.out
