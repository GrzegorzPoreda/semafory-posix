/*
----------------------------------------------------------------------------------------------------------
 autor: Grzegorz Poreda                                                                        22.06.2020
----------------------------------------------------------------------------------------------------------

Cwiczenie 6
Problem wzajemnego wykluczania procesow - semafory standardu POSIX.
waga = 1.5

Plik zrodlowy zawierajacy definicje funkcji do tworzenia, otwierania, uzyskiwania wartosci, operowania,
zamykania i usuwania semafora (korzystajacych z odpowiednich funkcji systemowych/bibliotecznych i
zawierajacych obsluge bledow)

*/

#include <stdio.h>		// perror
#include <stdlib.h>		// exit
#include <semaphore.h>	// sem_open, sem_close, sem_unlink, sem_post, sem_wait, sem_getvalue,
#include <sys/stat.h>	// sem_open
#include <fcntl.h>		// sem_open


/* TWORZENIE SEMAFORA */
sem_t *Sem_open_new(const char *name, int oflag, mode_t mode, unsigned int value)
{
	sem_t *adres = sem_open(name, oflag, mode, value);
	// utworz semafor i zapamietaj jego adres
	if(adres == SEM_FAILED)
	{
		perror("sem_open error");
		exit(1);
	}
	return adres;	// zwroc adres utworzonego semafora
}

/* OTWIERANIE SEMAFORA */
sem_t *Sem_open(const char *name, int oflag)
{
	sem_t *adres = sem_open(name, oflag);
	// otworz semafor i zapamietaj jego adres
	if(adres == SEM_FAILED)
	{
		perror("sem_open error");
		exit(1);
	}
	return adres;	// zwroc adres utworzonego semafora
}

/* UZYSKIWANIE WARTOSCI */
int Sem_getvalue(sem_t *sem, int *sval)
{
	if(sem_getvalue(sem, sval) == -1)	// przypisz wartosc semafora pod sval
	{
		perror("sem_getvalue error");
		exit(1);
	}
	return 0;	// sukces - zwroc 0
}

/* PODNOSZENIE O 1 WARTOSCI SEMAFORA */
int Sem_post(sem_t *sem)
{
	if(sem_post(sem) == -1)	// podnies o 1 wartosc semafora
	{
		perror("sem_post error");
		exit(1);
	}
	return 0;	// sukces - zwroc 0
}

/* OPUSZCZANIE O 1 WARTOSCI SEMAFORA */
int Sem_wait(sem_t *sem)
{
	if(sem_wait(sem) == -1)	// opusc o 1 wartosc semafora
	{
		perror("sem_wait error");
		exit(1);
	}
	return 0;	// sukces - zwroc 0
}

/* ZAMYKANIE SEMAFORA */
int Sem_close(sem_t *sem)
{
	if(sem_close(sem) == -1)	// zamknij semafor
	{
		perror("sem_close error");
		exit(1);
	}
	return 0;	// sukces - zwroc 0
}

/* USUWANIE SEMAFORA */
int Sem_unlink(const char *name)
{
	if(sem_unlink(name) == -1)	// usun semafor
	{
		perror("sem_unlink error");
		exit(1);
	}
	return 0;	// sukces - zwroc 0
}


