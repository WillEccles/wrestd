OUTPUT=testing.out
CPPFLAGS=-std=c++14
LINKFLAGS=-L../output/ -lwrestd -I../output/include/

all: $(OUTPUT) ../output

../output:
	@cd ../; make

$(OUTPUT): testing.cpp
	g++ $(LINKFLAGS) testing.cpp -o $(OUTPUT) $(CPPFLAGS)

clean:
	rm $(OUTPUT)
