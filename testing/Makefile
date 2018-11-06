OUTPUT=testing.out
CPPFLAGS=-std=c++14
LINKFLAGS=-I../src/

all: $(OUTPUT)

$(OUTPUT): testing.cpp
	g++ $(LINKFLAGS) testing.cpp -o $(OUTPUT) $(CPPFLAGS)

clean:
	rm $(OUTPUT)
