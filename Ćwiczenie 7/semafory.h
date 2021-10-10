#ifndef SEMAFORY_H
#define SEMAFORY_H

#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

sem_t *stworz_semafor (const char *name, int value);
sem_t *otworz_semafor (const char *name);
void zamknij_semafor (sem_t *sem_t);
int wartosc_semafor (sem_t *sem);
void podnies_semafor (sem_t *sem);
void opusc_semafor (sem_t *sem);
void usun_semafor (const char *name);

#endif