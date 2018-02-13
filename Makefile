CPPFLAGS=sdf
OUTDIR=output
OBJDIR=$(OUTDIR)/obj
HDIR=$(OUTDIR)/include
CXXFLAGS=-I /src -std=c++14 -fPIC -c

# add any .cpp files to this list, OBJS converts them all to .o for later use
SRCS=io.cpp strings.cpp stack.cpp queue.cpp stack.cpp queue.cpp binarysearchtree.cpp
OBJS=$(addprefix $(OBJDIR)/,$(subst .cpp,.o,$(SRCS)))

OUTLIB=$(OUTDIR)/libwrestd.so

all: dirs $(OUTLIB)

# creates necessary output dirs
dirs:
	@mkdir -p $(OBJDIR) $(HDIR)
	@cp src/*.h $(HDIR)/

$(OUTLIB): $(OBJS)
	$(CXX) -dynamiclib $(OBJS) -o $(OUTLIB)

$(OBJDIR)/%.o: src/%.cpp src/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

test:
	@cd testing/; make

clean:
	@rm -rf output
