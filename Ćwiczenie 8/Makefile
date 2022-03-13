DIR = `basename $(CURDIR)`

NAME1 = serwer
NAME2 = klient
LIB1 = kolejki

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

LIBS1  = $(LIB1).c

CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O
LDLIBS = -lrt

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

.PHONY: run8

runKlient: $(EXEC2)
	./$(EXEC2)

run8: $(EXEC1) $(EXEC2)
	xterm -hold -title SERWER -bg navy -e ./$(EXEC1) &
	xterm -hold -title KLIENT1 -bg darkgreen -e ./$(EXEC2) &
	xterm -hold -title KLIENT2 -bg darkgreen -e ./$(EXEC2) &
	xterm -hold -title KLIENT3 -bg darkgreen -e ./$(EXEC2)

.PHONY: clean tar

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )