# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
ODIR =object
CC =g++
CFLAGS =-I$(IDIR) -l cryptopp


cryptTest: cpp_exe.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ cryptTest
