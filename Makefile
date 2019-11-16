CXX=g++

CSVLIBDIR=libcsv-3.0.3
CSVLIB=libcsv.a

INCDIR=./include
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj
TESTBINDIR=./testbin

CXXFLAGS = --std=c++14 -I $(INCDIR) $(CSVLIBDIR)
TESTLDFlAGS= -lgtest -lgtest_main -lpthread

CSVOBJS=$(OBJDIR)/CSVReader.o

CSVTEST=testcsv

all: $(CSVLIBDIR)/.libs/$(CSVLIB) directories RUNTESTS

RUNTESTS: RUNCSVTEST

RUNCSVTEST: $(TESTBINDIR)/$(CSVTEST)
	$(TESTBINDIR)/$(CSVTEST)

$(CSVLIBDIR)/.libs/$(CSVLIB): $(CSVLIBDIR)/Makefile
	cd $(CSVLIBDIR); make ; cd ..

$(CSVLIBDIR)/Makefile:
	cd $(CSVLIBDIR); ./configure ; cd ..

$(TESTBINDIR)/$(CSVTEST): $(OBJDIR)/testcsv.o $(CSVOBJS) $(CSVLIBDIR)/.libs/$(CSVLIB)
	$(CXX) $(CXXFLAGS) $(OBJDIR)/testcsv.o $(CSVOBJS) $(CSVLIBDIR)/.libs/$(CSVLIB) -o $(TESTBINDIR)/$(CSVTEST) $(TESTLDFlAGS)

$(OBJDIR)/testcsv.o: $(SRCDIR)/testcsv.cpp $(INCDIR)/CSVreader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)testcsv.cpp -c -o $(OBJDIR)/testcsv.o

$(OBJDIR)/CSVreader.o: $(SRCDIR)/CSVreader.cpp $(INCDIR)/CSVreader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)CSVreader.cpp -c -o $(OBJDIR)/CSVreader.o

directories: $(BINDIR) $(OBJDIR) $(TESTBINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	
$(TESTBINDIR):
	mkdir -p $(TESTBINDIR)
	
clean:
	cd $(CSVLIBDIR); make clean ; cd ..
	rm -f $(CSVLIBDIR)/Makefile