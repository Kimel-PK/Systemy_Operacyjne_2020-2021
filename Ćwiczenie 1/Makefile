DIR = `basename $(CURDIR)`

NAME1 = programA
NAME2 = programB
NAME3 = programC
NAME4 = programD
NAME5 = programE

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x
EXEC3  = $(NAME3).x
EXEC4  = $(NAME4).x
EXEC5  = $(NAME5).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS2) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3) $(LIBS3) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4) $(LIBS4) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC5): $(OBJS5) $(LIBS5) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: runA runB runC runD runE

runA: $(EXEC1)
	clear
	./$(EXEC1)

runB: $(EXEC2)
	clear
	./$(EXEC2)

runC: $(EXEC3)
	clear
	./$(EXEC3)

runD: $(EXEC4)
	clear
	./$(EXEC4)

runE: $(EXEC5)
	clear
	./$(EXEC5)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
