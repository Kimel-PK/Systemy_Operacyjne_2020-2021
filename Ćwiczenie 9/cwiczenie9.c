#define _REENTRANT
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "watki.h"

#define max_liczba_watkow 10

int liczba;
unsigned int liczba_watkow;
unsigned int liczba_sekcji;
pthread_t watki[max_liczba_watkow];
pthread_mutex_t mutex;
const double min_dlugosc_czekania = 1.0;
const double max_dlugosc_czekania = 4.0 - min_dlugosc_czekania;

void ustaw_kursor (unsigned x, unsigned y) {
    printf ("\033[%d;%dH\033[2K", y, x);
}

void *watek_start (void *argument) {

    int licznik = 0;
    int numer_watku = *(int *)argument;
    srand (time (NULL));

    printf ("Wątek nr: %d, ID: %ld \n", numer_watku + 1, watki[numer_watku]);

    sleep (1);

    for (int i = 0; i < liczba_sekcji; i++) {

        ustaw_kursor (0, 4 + liczba_watkow + numer_watku);
        printf("\033[32mWątek nr: %d, SP: %d, liczba: %d \033[0m\n", numer_watku + 1, i + 1, liczba);

        // czekaj losową ilość czasu
        sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);
    
        // sekcja krytyczna
        zamknij_mutex(&mutex);

        ustaw_kursor (25, 4 + liczba_watkow + numer_watku);
        printf("\033[1;31mWątek nr: %d, SK: %d, liczba: %d \033[0m\n", numer_watku + 1, i + 1, liczba);
    
        // dodaj 1 do liczby
        licznik = liczba;
        licznik++;

        // czekaj losową ilość czasu
        sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);

        liczba = licznik;

        // koniec sekcji krytycznej
        otworz_mutex (&mutex);
    
        ustaw_kursor (0, 4 + liczba_watkow + numer_watku);
        printf("\033[32mWątek nr: %d, SP: %d, liczba: %d \033[0m\n", numer_watku + 1, i + 1, liczba);
    
        // czekaj losową ilość czasu
        sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);

    }

    return 0;
}

int main (int argc, char *argv[]) {

    // sprawdzenie poprawności argumentów
    if (argc != 3) {
        printf ("Błąd: niepoprawna liczba argumentów!\n");
        printf ("Wywołaj program wpisując: %s ilość_wątków ilość_sekcji\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    liczba_watkow = atoi(argv[1]);
    if (liczba_watkow > max_liczba_watkow) {
        printf ("Ilość wątków przekracza dozwoloną ilość!\n");
        printf ("Maksymalna dozwolona ilość wątków: %d\n", max_liczba_watkow);
        exit (EXIT_FAILURE);
    }
	liczba_sekcji = atoi(argv[2]);

	inicjalizuj_mutex (&mutex);
	printf("Zainicjalizowano mutex o adresie %p\n", (void *)&mutex);

    liczba = 0;

    // utwórz podaną liczbę wątków
	for (int i = 0; i < liczba_watkow; i++) {

        int *pamiec = malloc (sizeof (int));
        *pamiec = i;

        // utwórz wątek i przekaż mu jako argument jego numer
        sleep ((double)i/liczba_watkow);
        watki[i] = utworz_watek (watek_start, (void *)pamiec);

	}

    // czekaj na zakończenie wątków
    for (int i = 0; i < liczba_watkow; i++) {
        polacz_watek (watki[i]);
    }

    ustaw_kursor (0, 4 + liczba_watkow * 2);

    // sprawdź czy synchronizacja się powiodła
	if (liczba != liczba_watkow * liczba_sekcji) {
		printf ("Synchronizacja nie powiodła się!\nOczekiwano: %d\nOtrzymano: %d\n", (liczba_watkow * liczba_sekcji), liczba);
	} else {
        printf ("Synchronizacja powiodła się!\nOczekiwano: %d\nOtrzymano: %d\n", (liczba_watkow * liczba_sekcji), liczba);
    }

    usun_mutex (&mutex);

    return 0;
}