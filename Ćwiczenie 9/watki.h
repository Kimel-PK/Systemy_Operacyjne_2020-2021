#ifndef WATKI_H
#define WATKI_H

#include <pthread.h>

// utwórz nowy wątek, który rozpocznie wykonywać "funkcja" i przyjmie "argument"
pthread_t utworz_watek (void *funkcja(void *), void *argument);
// czekaj na zakończenie i połącz wątek
void polacz_watek (pthread_t watek);
// inicjalizuj mutex
void inicjalizuj_mutex (pthread_mutex_t *mutex);
// zamknij mutex (wejdź do sekcji krytycznej)
void zamknij_mutex (pthread_mutex_t *mutex);
// otwórz mutex (wyjdź z sekcji krytycznej)
void otworz_mutex (pthread_mutex_t *mutex);
// usuń mutex
void usun_mutex (pthread_mutex_t *mutex);

#endif