# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
ODIR=object
CC=clang
CFLAGS=-I$(IDIR)



_DEPS = mycrypt.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cryptTest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ cryptTest
