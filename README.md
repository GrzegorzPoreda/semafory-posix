# Semafory POSIX
Autor: Grzegorz Poreda, 22.06.2020

----------------------------------------------------------------------------

I.  Problem wzajemnego wykluczania procesow - semafory standardu
	POSIX.
    Program sklada sie z 5 modulow:
  1) powielacz.c  - program glowny
  2) wykluczacz.c  - program dla exec
  3) biblioteki.h  - plik naglowkowy z plikami naglowkowymi bibliotek i definicjami stalych
  4) sem_lib.c  - plik zrodlowy zawierajacy definicje funkcji dla semaforow
  5) sem_lib.h  - plik naglowkowy zawierajacy deklaracje funkcji dla
	semaforow
	
II. Problem wzajemnego wykluczania procesow - semafory standardu POSIX (wersja bez uzycia sekcji krytycznej)
    Program sklada sie z 5 modulow: 
  1) powielacz.c  - program glowny
  2) wykluczacz2.c  - program dla exec
  3) biblioteki.h  - plik naglowkowy z plikami naglowkowymi bibliotek idefinicjami stalych
  4) sem_lib.c  - plik zrodlowy zawierajacy definicje funkcji dlasemaforow
  5) sem_lib.h  - plik naglowkowy zawierajacy deklaracje funkcji dlasemaforow

----------------------------------------------------------------------------

* Jak uruchomic programy:

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic 1-szy program, nalezy wykonac komende: **make run**

-> Aby uruchomic 2-gi program, nalezy wykonac komende: **make runB**

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac: **make clean**

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac: **make tar**
