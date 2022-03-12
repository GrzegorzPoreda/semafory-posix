#####################################################################
# autor: Grzegorz Poreda                                 22.06.2020
#####################################################################


#####################################################################
#                            Makefile
#####################################################################
# make all, run, clean, tar
#####################################################################

.SUFFIXES: .c .o .h .x .txt

#####################################################################
#                              MAKRA
#####################################################################

# Kompilator i linker
CO = gcc
LD = $(CO)

# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic -pthread

# Nazwy
NAME1 = powielacz
NAME2 = sem_lib
NAME3 = wykluczacz
NAME4 = biblioteki
NAME5 = $(NAME3)2

# Ilosc procesow potomnych
FORK_NUM = 3

# Ilosc sekcji krytycznych
CRITICAL = 3

# Pliki zrodlowe
SRC1 = $(NAME1).c
SRC2 = $(NAME2).c
SRC3 = $(NAME3).c
SRC5 = $(NAME5).c

# Pliki naglowkowe
HEADS2 = $(NAME2).h
HEADS4 = $(NAME4).h

# Pliki objectowe
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS5 = $(NAME5).o

# Pliki wykonawcze
EXEC1 = $(NAME1).x
EXEC3 = $(NAME3).x
EXEC5 = $(NAME5).x

# Pliki tekstowe
TXT2 =

# Wykonanie programow
RUN = run
RUNB = runB

# Nazwa katalogu cwiczenia
DIR = `basename $(CURDIR)`

#####################################################################
#                            Domyslny cel
#####################################################################

.PHONY: all
all: $(EXEC1)

#####################################################################
#                          Reguly wzorcowe
#####################################################################

# Pliki objectowe
%.o: %.c
	$(CO) $(CFLAGS) -c $<

# Pliki wykonawcze
%.x: %.o
	$(LD) -o $@ $(LFLAGS) $<

#####################################################################
#                   Programy powielacz i wykluczacz
#####################################################################

$(EXEC1): $(OBJS1) $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(OBJS1): $(SRC1) $(HEADS2) $(HEADS4)
	$(CO) $(CFLAGS) -c $<

$(EXEC3): $(OBJS3) $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(OBJS3): $(SRC3) $(HEADS2) $(HEADS4)
	$(CO) $(CFLAGS) -c $<

.PHONY: $(RUN)
$(RUN): $(EXEC1) $(EXEC3)
	./$(EXEC1) $(EXEC3) $(FORK_NUM) $(CRITICAL)

#####################################################################
#       Programy powielacz i wykluczacz (bez sekcji krytycznej)
#####################################################################

$(EXEC5): $(OBJS5) $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(OBJS5): $(SRC5) $(HEADS2) $(HEADS4)
	$(CO) $(CFLAGS) -c $<

.PHONY: $(RUNB)
$(RUNB): $(EXEC1) $(EXEC5)
	./$(EXEC1) $(EXEC5) $(FORK_NUM) $(CRITICAL)

#####################################################################
#                          Sprzataczka
#####################################################################

.PHONY: clean tar

clean:
	rm -f *.o *.x *.txt

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
