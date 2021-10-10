#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "semafory.h"
#include "dzielona.h"

#define NELE 10 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // Liczba elementow bufora

// Segment pamieci dzielonej
typedef struct {
    char bufor[NBUF][NELE]; // Wspolny bufor danych
    int zapis;
    int odczyt;
} SegmentPD;

// argumenty [0] nazwa_programu [1] SEMAFOR_PRODUCENT [2] SEMAFOR_KONSUMENT [3] NAZWA_PD [4] PLIK_WE
int main (int argc, char *argv[]) {

    int plik;
    int PD_desk;
    SegmentPD *PD;
    sem_t *semafor_producent;
    sem_t *semafor_konsument;
    int odczyt;
    const double max_dlugosc_czekania = 2.0;

    // sprawdzenie poprawności argumentów
    if (argc != 5) {
        printf ("Błąd: niepoprawna liczba argumentów!\n");
        printf ("Wywołaj program wpisując: %s semafor_producent semafor_konsument nazwa_pd plik_we\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    srand(time(NULL));

    if ((plik = open (argv[4], O_RDONLY, 0644)) == -1) {
        printf ("Błąd otwarcia pliku %s do odczytu\n", argv[1]);
        perror ("Błąd pliku");
        exit (EXIT_FAILURE);
    }

    semafor_producent = otworz_semafor (argv[1]);
    printf ("Producent: otwarto semafor producenta %s deskryptor %p\n", argv[1], (void *)semafor_producent);
    semafor_konsument = otworz_semafor (argv[2]);
    printf ("Producent: otwarto semafor konsumenta %s deskryptor %p\n", argv[2], (void *)semafor_konsument);

    PD_desk = otworz_PD (argv[3]);
    printf ("Producent: pamięć dzielona %s deskryptor %d\n", argv[3], PD_desk);

    PD = (SegmentPD *) odwzoruj_PD (PD_desk, sizeof(SegmentPD));

    PD->zapis = 0;

    // zapisywanie wyprodukowanych produktów do pamięci dzielonej
    while (1) {

        // czekaj losową ilość czasu
        sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);

        // opuść semafor
        printf ("Producent: przed SK semafor: %d\n", wartosc_semafor(semafor_producent));
        opusc_semafor (semafor_producent);

        odczyt = read(plik, PD->bufor[PD->zapis], NELE);
        if (odczyt == -1) {
            printf("Błąd odczytu z pliku\n");
            exit(EXIT_FAILURE);
        } if (odczyt != NELE) {
            PD->bufor[PD->zapis][odczyt] = '\0';
            printf ("\tProdukuje => (%ld) %s\n", strlen (PD->bufor[PD->zapis]), PD->bufor[PD->zapis]);
            printf ("Producent: koniec pliku\n");

            // podnieś semafor konsumenta ostatni raz
            podnies_semafor (semafor_konsument);
            printf ("Producent: po SK semafor: %d\n", wartosc_semafor (semafor_konsument));

            break;
        } else {
            if(write (STDOUT_FILENO, "\tProdukuje => (10) ", 19) == -1) {
                perror("Błąd write na ekran");
                exit(EXIT_FAILURE);
            }
            if(write (STDOUT_FILENO, PD->bufor[PD->zapis], NELE) == -1) {
                perror("Błąd write na ekran");
                exit(EXIT_FAILURE);
            }
            printf ("\n\tIndeks bufora zapis: %d\n", PD->zapis);
        }
        PD->zapis = (PD->zapis + 1) % NBUF;

        // podnieś semafor konsumenta
        podnies_semafor (semafor_konsument);
        printf ("Producent: po SK semafor: %d\n", wartosc_semafor (semafor_konsument));

    }

    if (close (plik) == -1) {
        perror ("Błąd zamknięcia pliku wyjścia");
        exit (EXIT_FAILURE);
    }

    usun_odwzorowanie_PD(PD, sizeof(SegmentPD));

    zamknij_PD (PD_desk);
    zamknij_semafor(semafor_producent);
    zamknij_semafor(semafor_konsument);

    printf ("Producent: koniec procesu\n");

    return 0;

}