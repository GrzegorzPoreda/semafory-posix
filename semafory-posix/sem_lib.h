/*
----------------------------------------------------------------------------------------------------------
 autor: Grzegorz Poreda                                                                        22.06.2020
----------------------------------------------------------------------------------------------------------

Cwiczenie 6
Problem wzajemnego wykluczania procesow - semafory standardu POSIX.
waga = 1.5

Plik naglowkowy zawierajacy deklaracje funkcji do tworzenia, otwierania, uzyskiwania wartosci, operowania,
zamykania i usuwania semafora (korzystajacych z odpowiednich funkcji systemowych/bibliotecznych i
zawierajacych obsluge bledow)

*/


#ifndef SEM_LIB_h
#define SEM_LIB_h

sem_t *Sem_open_new(const char *name, int oflag, mode_t mode, unsigned int value);
sem_t *Sem_open(const char *name, int oflag);
int Sem_getvalue(sem_t *sem, int *sval);
int Sem_post(sem_t *sem);
int Sem_wait(sem_t *sem);
int Sem_close(sem_t *sem);
int Sem_unlink(const char *name);

#endif // SEM_LIB_h