DIR = `basename $(CURDIR)`

NAME1 = program4
PLIK_WE = surowce
PLIK_WY = skonsumowane

EXEC1  = $(NAME1).x

OBJS1  = $(NAME1).o

CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run4

run4: $(EXEC1)
	clear
	./$(EXEC1) $(PLIK_WE) $(PLIK_WY)
	@echo "\n=============================\n"
	@diff -s $(PLIK_WE) $(PLIK_WY)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )