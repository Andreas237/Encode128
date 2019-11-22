# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
ODIR=object
CC=g++



# Detect whether Mac due to Crypto++ location
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CFLAGS=-L /usr/include/cryptopp -I$(IDIR) -l cryptopp -std=c++11
endif
ifeq ($(UNAME_S),Darwin)
   CFLAGS=-I$(IDIR) -l cryptopp -Wc++11-extensions
endif


_DEPS = encryption_parameters.h LEA_run.h AES_run.h naive.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Cryptest.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: Cryptest Benchmark

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Cryptest: Crypto_Tests.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

Benchmark: Benchmark.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)




.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ Cryptest Benchmark
