/*
----------------------------------------------------------------------------------------------------------
 autor: Grzegorz Poreda                                                                        22.06.2020
----------------------------------------------------------------------------------------------------------

Cwiczenie 6
Problem wzajemnego wykluczania procesow - semafory standardu POSIX.
waga = 1.5

Plik zrodlowy "wykluczacza", czyli programu implementujacego wzajemne wykluczanie.

*/


#include "biblioteki.h"


int main(int argc, char* argv[])	// argumenty: numer_procesu liczba_procesow_potomnych nazwa_semafora
{
	int proc_num;	// numer procesu
	sscanf(argv[1], "%d", &proc_num);
	printf("\n>>> Utworzony WYKLUCZACZ %d o PID: %d", proc_num, getpid());
	
	int CRITICAL;	// liczba sekcji krytycznych
	sscanf(argv[2], "%d", &CRITICAL);
	
	sem_t *adres = Sem_open(argv[3],0);	// otwarcie semafora i pobranie jego adresu
	printf("\nWYKLUCZACZ %d >>> Otworzylem semafor %s", proc_num, NAME);
	
	
	int value;	// aktualna wartosc semafora
	
	int i;
	for(i=0;i<CRITICAL;i++)
	{
		/* ----- Sekcja prywatna (przed sekcja krytyczna) ----- */
		Sem_getvalue(adres, &value);	// uzyskanie wartosci semafora
		printf("\nWYKLUCZACZ %d >>> Sekcja prywatna nr %d (przed sekcja krytyczna); ", proc_num, i+1);
		printf("Wartosc semafora: %d", value);
		sleep(rand() % RANDOM);	// sleep z losowa iloscia sekund
		Sem_wait(adres);
		
		
		
		/* ----- Sekcja krytyczna ----- */
		Sem_getvalue(adres, &value);	// uzyskanie wartosci semafora
		printf("\n\t\t\t\tWYKLUCZACZ %d >>> Sekcja krytyczna nr %d; ", proc_num, i+1);
		printf("Wartosc semafora: %d", value);
		
		int PLIK = open(TXT,O_RDONLY,0644);	//otwarcie pliku do odczytu
		if (PLIK == -1)	//obsluga bledu open
		{
			perror("open error");
			exit(6);
		}
		
		char bufor[NBYTE_WYK];	// bufor na wartosc z pliku
		
		int READ;
		bool WHILE = true;
		while(WHILE)
		{
			switch(READ = read(PLIK,bufor,NBYTE_WYK)) // czytanie z pliku do bufora
			{
				case -1: // obsluga bledu read
					perror("read error");
					exit(8);
				case 0:; // zakonczenie czytania
					WHILE = false;
			};
		}
		
		if (close(PLIK) == -1)	// zamkniecie pliku do odczytu i obsluga bledu close
		{
			perror("close error");
			exit(9);
		}
		
		int liczba;
        sscanf(bufor, "%d", &liczba);
		liczba ++;
		sprintf(bufor, "%d", liczba);
		
		sleep(rand() % RANDOM);	// sleep z losowa iloscia sekund
		
		PLIK = open(TXT,O_WRONLY,0666);	//otwarcie pliku do zapisu
		if (PLIK == -1)	//obsluga bledu open
		{
			perror("open error");
			exit(6);
		}
		
		int WRITE = write(PLIK,bufor,NBYTE_WYK);	// zapis z bufora do pliku		
		if (WRITE == -1)	// obsluga bledu write
		{
			perror("write error");
			exit(7);
		}
		printf("\nWYKLUCZACZ %d >>> Dane zapisane z bufora do pliku %s:\n", proc_num, TXT);
		write(STDOUT_FILENO,bufor,NBYTE_WYK);	// wypisanie na ekran zapisanych danych	
		
		if (close(PLIK) == -1)	// zamkniecie pliku do zapisu i obsluga bledu close
		{
			perror("close error");
			exit(9);
		}
		
		Sem_post(adres);
		
		

		/* ----- Sekcja prywatna (po sekcji krytycznej) ----- */
		Sem_getvalue(adres, &value);	// uzyskanie wartosci semafora
		printf("\nWYKLUCZACZ %d >>> Sekcja prywatna nr %d (po sekcji krytycznej); ", proc_num, i+1);
		printf("Wartosc semafora: %d", value);
	}
	
	Sem_close(adres);	// zamkniecie semafora
	printf("\nWYKLUCZACZ %d >>> Zamknalem semafor %s", proc_num, NAME);
	
	return 0;
}