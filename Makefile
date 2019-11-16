CXX=g++

CSVLIBDIR=libcsv-3.0.3
CSVLIB=libcsv.a

all: $(CSVLIBDIR)/.libs/$(CSVLIB)

$(CSVLIBDIR)/.libs/$(CSVLIB): $(CSVLIBDIR)/Makefile
	cd $(CSVLIBDIR); make ; cd ..

$(CSVLIBDIR)/Makefile:
	cd $(CSVLIBDIR); ./configure ; cd ..

clean:
	cd $(CSVLIBDIR); make clean ; cd ..
	rm -f $(CSVLIBDIR)/Makefile