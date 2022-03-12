/*
----------------------------------------------------------------------------------------------------------
 autor: Grzegorz Poreda                                                                        22.06.2020
----------------------------------------------------------------------------------------------------------

Cwiczenie 6
Problem wzajemnego wykluczania procesow - semafory standardu POSIX.
waga = 1.5

Plik zrodlowy "powielacza" czyli programu tworzacego semafor, procesy potomne i usuwajacego semafor.


POLECENIE:

Przy pomocy semaforow nazwanych standardu POSIX zaimplementowac zadanie wzajemnego wykluczania dla
procesow. Czas operacji na wspolnym zasobie symulowac uzywajac np. funkcji sleep. Dla demonstracji
poprawnosci dzialania programu uzyc odpowiednich komunikatow wypisywanych przez poszczegolne procesy
przed, w trakcie i po sekcji krytycznej oraz funkcji podajacej wartosc semafora. Pamietac o
zainicjowaniu semafora odpowiednia wartoscia zaraz po jego utworzeniu.

Stworzyc wlasna biblioteke prostych w uzyciu funkcji do: tworzenia, otwierania, uzyskiwania wartosci,
operowania, zamykania i usuwania semafora (korzystajacych z odpowiednich funkcji
systemowych/bibliotecznych i zawierajacych obsluge bledow). 

Napisac specjalny program do powielania procesow realizujacych wzajemne wykluczanie – w oparciu o
funkcje fork i exec (nazwe programu do inicjowania procesow, liczbe procesow oraz liczbe sekcji
krytycznych/prywatnych kazdego procesu przekazywac przez argumenty programu "powielacza”). Program ten
powinien na poczatku utworzyc i zainicjowac semafor, a na koncu – kiedy wszystkie jego procesy potomne
zakoncza swoje dzialanie – usunac go.

W celu weryﬁkacji poprawnosci wzajemnego wykluczania procesow niech program "powielacz” na samym
poczatku stworzy plik tekstowy numer.txt i wpisze w nim numer o wartosci 0 (zero), a program
implementujacy wzajemne wykluczanie w swojej sekcji krytycznej odczytuje wartosc zapisanego w tym pliku
numeru, nastepnie zwieksza go o 1 i po pewnej (np. losowej) chwili czasu zapisuje z powrotem do pliku.
Po zakonczeniu dzialania wszystkich procesow realizujacych wzajemne wykluczanie proces "powielacz”
powinien sprawdzic poprawnosc koncowego numeru zapisanego w pliku i wypisac odpowiedni komunikat.

Sprawdzic rowniez jaka bedzie koncowa wartosc numeru bez uzycia sekcji krytycznej.

*/


#include "biblioteki.h"	// pliki naglowkowe bibliotek i definicje stalych


int main(int argc, char* argv[])
{
	if (argc != 4)  //obsluga bledu podania zlej liczby argumentow przy uruchamianiu
	{
		printf("Blad. Poprawne wywolanie: ./powielacz.x  nazwa_programu_dla_exec ");
		printf("liczba_procesow_potomnych liczba_sekcji_krytycznych\n");
		printf("np. ./powielacz.x wykluczacz.c 3 3 \n");
		exit(11);
	}
	
	printf("\nPOWIELACZ >>> Moj PID: %d\n", getpid());
	
	int FORK_NUM;	// liczba procesow potomnych
	sscanf(argv[2], "%d", &FORK_NUM);
	
	int CRITICAL;	// liczba sekcji krytycznych
	sscanf(argv[3], "%d", &CRITICAL);
	
	char SemName[SLEN];	// nazwa semafora ze znakiem "/" na poczatku
	sprintf(SemName,"%s%s",SEM_NAME,NAME);
	
	int PLIK = open(TXT, O_WRONLY | O_CREAT, 0666);	// utworzenie/otwarcie pliku do zapisu
	if (PLIK == -1)	//obsluga bledu open
	{
		perror("open error");
		exit(6);
	}
	
	printf("POWIELACZ >>> Utworzylem plik do zapisu %s\n", TXT);
	
	char zapis[NBYTE_POW] = "0";
	
	int WRITE = write(PLIK,zapis,NBYTE_POW);	// zapis 0 do pliku		
	if (WRITE == -1)	// obsluga bledu write
	{
		perror("write error");
		exit(7);
	}
	printf("POWIELACZ >>> Dane zapisane do pliku %s:\n", TXT);
	write(STDOUT_FILENO,zapis,NBYTE_POW);	// wypisanie na ekran zapisanych danych	
	
	if(close(PLIK) == -1)	// zamkniecie pliku do zapisu i obsluga bledu close
	{
		perror("close error");
		exit(9);
	}
	printf("\nPOWIELACZ >>> Zamknalem plik %s\n", TXT);
	
	sem_t *adres = Sem_open_new(SemName, O_CREAT | O_EXCL, 0666, BEGIN_VALUE);	// utworzenie semafora
	int value;	// aktualna wartosc semafora
    Sem_getvalue(adres, &value);	// uzyskanie wartosci semafora
	
	printf("POWIELACZ >>> Utworzylem semafor %s o adresie %p i wartosci %d\n\n", NAME, (void*)&adres, value);
	
	int i;
	for(i=0;i<FORK_NUM;i++)
	{
		char proc_num[FORK_NUM];	// numer procesu
		sprintf(proc_num, "%d", i);
		switch(fork())
		{
			case -1:    //obsluga bledu forka
				perror("fork error");
				exit(1);
			case 0:; /* proces potomny */
				char PathName[PLEN];
				sprintf(PathName,"%s%s",PATH,argv[1]);
				execl(PathName,argv[1],proc_num,argv[3],SemName,NULL);
				//obsluga bledu execl:
				perror("execl error");
				_exit(2);
			default: /* proces macierzysty */
				sleep(0);
		};
	}
	
	for(i=0;i<FORK_NUM;i++)
	{
		if(wait(0) == -1)	//czekaj na zakonczenie procesow potomnych
		{
			perror("wait error");
			exit(1);
		}
	}
	
	PLIK = open(TXT,O_RDONLY,0644);	//otwarcie pliku do odczytu
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
	
	int liczba;	// liczba w formacie int
    sscanf(bufor, "%d", &liczba);
	
	printf("\n\nWartosc numeru z pliku %s: %d\n", TXT, liczba);
	printf("Wartosc oczekiwana: %d\n", FORK_NUM * CRITICAL);
	if(liczba == FORK_NUM*CRITICAL) printf("\nSukces! Wartosci sie zgadzaja.\n");
	if(liczba != FORK_NUM*CRITICAL) printf("\nPorazka! Wartosci sie nie zgadzaja.\n");
	
	Sem_unlink(SemName);	// usun semafor
	printf("\nPOWIELACZ >>> Usunalem semafor %s\n\n", NAME);
	
	return 0;
}

