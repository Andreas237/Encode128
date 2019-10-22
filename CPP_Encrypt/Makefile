# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
ODIR=object
CC=g++
CFLAGS=-L /usr/include/cryptopp -I$(IDIR) -l cryptopp


_DEPS = encryption_parameters.h LEA_run.h AES_run.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Cryptest.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: Cryptest

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Cryptest: Crypto_Tests.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)




.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ Cryptest
