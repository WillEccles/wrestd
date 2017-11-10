CPPFLAGS=sdf
OUTDIR=output
OBJDIR=$(OUTDIR)/obj
LIBDIR=$(OUTDIR)/lib
HDIR=$(OUTDIR)/headers/wrestd
CPPFLAGS=-I /src -std=c++14 -fPIC -c

# add any .cpp files to this list, OBJS converts them all to .o for later use
SRCS=io.cpp strings.cpp stack.cpp queue.cpp stack.cpp queue.cpp
OBJS=$(addprefix $(OBJDIR)/,$(subst .cpp,.o,$(SRCS)))

OUTLIB=$(LIBDIR)/libwrestd.so

all: dirs $(OUTLIB)

# creates necessary output dirs
dirs:
	@mkdir -p $(OBJDIR) $(LIBDIR) $(HDIR)
	@cp src/*.h $(HDIR)/

$(OUTLIB): $(OBJS)
	g++ -dynamiclib $(OBJS) -o $(OUTLIB)

$(OBJDIR)/%.o: src/%.cpp src/%.h
	g++ $(CPPFLAGS) $< -o $@

test:
	@cd testing/; make

clean:
	@rm -rf output
