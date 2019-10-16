# Thanks again!
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =include
CC=clang
CFLAGS=-I$(IDIR)

ODIR=object

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
