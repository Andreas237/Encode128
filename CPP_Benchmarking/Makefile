# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
ODIR=object
CC=g++



# Detect whether Mac due to Crypto++ location
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CFLAGS=-L /usr/include/cryptopp -I$(IDIR) -l cryptopp
endif
ifeq ($(UNAME_S),Darwin)
   CFLAGS=-I$(IDIR) -l cryptopp
endif

# CFLAGS=-L /usr/include/cryptopp -I$(IDIR) -l cryptopp


_DEPS = encryption_parameters.h LEA_run.h AES_run.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Benchmark.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: Benchmark

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Benchmark: Benchmark.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)




.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ Benchmark
