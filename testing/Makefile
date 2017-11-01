OUTPUT=testing.out
CPPFLAGS=-std=c++14
LINKFLAGS=-L../output/lib/ -lwrestd -I../output/headers/

all: $(OUTPUT) ../output

../output:
	@cd ../; make

$(OUTPUT): testing.cpp
	g++ $(LINKFLAGS) testing.cpp -o $(OUTPUT) $(CPPFLAGS)

clean:
	rm $(OUTPUT)
