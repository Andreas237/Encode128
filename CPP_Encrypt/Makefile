# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
ODIR=object
CC=g++
CFLAGS=-I$(IDIR) -l cryptopp

all: CryptoppTest AESCrypt

CryptoppTest: cpp_exe.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


AESCrypt: AES_Test.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)




.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ CryptoppTest AESCrypt
