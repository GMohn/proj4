CXX=g++

CSVLIBDIR=libcsv-3.0.3
CSVLIB=libcsv.a

INCDIR=./include
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj
TESTBINDIR=./testbin

CXXFLAGS = --std=c++14 -I $(INCDIR) -I $(CSVLIBDIR)
TESTLDFlAGS= -lgtest -lgtest_main -lpthread
XMLLDFLAGS= -lexpat

CSVOBJS=$(OBJDIR)/CSVReader.o
XMLOBJS=$(OBJDIR)/XMLReader.o

CSVTEST=testcsv

all: $(CSVLIBDIR)/.libs/$(CSVLIB) directories RUNTESTS

RUNTESTS: RUNCSVTEST RUNXMLTEST

RUNCSVTEST: $(TESTBINDIR)/$(CSVTEST)
	$(TESTBINDIR)/$(CSVTEST)

RUNXMLTEST: $(TESTBINDIR)/$(XMLTEST)
	$(TESTBINDIR)/$(XMLTEST)

$(CSVLIBDIR)/.libs/$(CSVLIB): $(CSVLIBDIR)/Makefile
	cd $(CSVLIBDIR); make ; cd ..

$(CSVLIBDIR)/Makefile:
	cd $(CSVLIBDIR); ./configure ; cd ..

$(TESTBINDIR)/$(CSVTEST): $(OBJDIR)/testcsv.o $(CSVOBJS) $(CSVLIBDIR)/.libs/$(CSVLIB)
	$(CXX) $(CXXFLAGS) $(OBJDIR)/testcsv.o $(CSVOBJS) $(CSVLIBDIR)/.libs/$(CSVLIB) -o $(TESTBINDIR)/$(CSVTEST) $(TESTLDFlAGS)

$(OBJDIR)/testcsv.o: $(SRCDIR)/testcsv.cpp $(INCDIR)/CSVReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)/testcsv.cpp -c -o $(OBJDIR)/testcsv.o

$(OBJDIR)/CSVReader.o: $(SRCDIR)/CSVReader.cpp $(INCDIR)/CSVReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)/CSVReader.cpp -c -o $(OBJDIR)/CSVReader.o

$(TESTBINDIR)/$(XMLTEST): $(OBJDIR)/testxml.o $(XMLOBJS)
	$(CXX) $(CXXFLAGS) $(OBJDIR)/testxml.o $(XMLOBJS) -o $(TESTBINDIR)/$(XMLTEST) $(TESTLDFlAGS)

$(OBJDIR)/testxml.o: $(SRCDIR)/testxml.cpp $(INCDIR)/XMLReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)testxml.cpp -c -o $(OBJDIR)/testxml.o

$(OBJDIR)/XMLReader.o: $(SRCDIR)/XMLReader.cpp $(INCDIR)/XMLReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)XMLReader.cpp -c -o $(OBJDIR)/XMLReader.o

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
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
	rm -f $(TESTBINDIR)/*
