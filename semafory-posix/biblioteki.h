/*
----------------------------------------------------------------------------------------------------------
 autor: Grzegorz Poreda                                                                        22.06.2020
----------------------------------------------------------------------------------------------------------

Cwiczenie 6
Problem wzajemnego wykluczania procesow - semafory standardu POSIX.
waga = 1.5

Plik naglowkowy zawierajacy pliki naglowkowe bibliotek i definicje stalych

*/

#define RANDOM 4		// maksymalna liczba losowych liczb (od 0 do RANDOM-1)

#define SEM_NAME "/"	// znak dodawany do nazwy semafora
#define NAME "sem1"		// nazwa semafora
#define SLEN 252		// dlugosc nazwy semafora ze znakiem "/" na poczatku
#define BEGIN_VALUE 1	// poczatkowa wartosc semafora

#define TXT "numer.txt"
#define NBYTE_POW 1		// ilosc bajtow zapisywanych do pliku przez powielacz
#define NBYTE_WYK 2		// ilosc bajtow zapisywanych do pliku przez wykluczacz

#define PATH "./"   	// sciezka do pliku (bez nazwy)
#define PLEN 100    	// dlugosc sciezki do pliku

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// read, write, close, unlink, pipe
#include <sys/types.h>	// open, mkfifo
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>	// bool

#include <semaphore.h>	// sem_open, sem_close, sem_unlink, sem_post, sem_wait, sem_getvalue,
						// sem_init, sem_destory, 
#include <sys/stat.h>	// sem_open
#include <fcntl.h>		// sem_open

#include "sem_lib.h"	// moja wlasna biblioteka z operacjami semaforowymi i z obsluga bledow

