DIR = `basename $(CURDIR)`

NAME1 = cwiczenie9
WATKI = 4
SEKCJE = 2
LIB1 = watki

EXEC1  = $(NAME1).x

OBJS1  = $(NAME1).o

HEADS1 = $(LIB1).h
LIBS1  = $(LIB1).c

CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O
LDLIBS = -lpthread

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1) $(LIBS1)
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

$(OBJS1): $(HEADS1)

.PHONY: run9

run9: $(EXEC1)
	clear
	./$(EXEC1) $(WATKI) $(SEKCJE)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )