#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include "kolejki.h"

void wyjscie(void) {
    kolejka_usun (KOLEJKA_NAZWA);
}

void sygnal_wyjscie(int signal) {
    printf ("\nSygnał przerwania, usuwanie kolejki\n");
    exit(EXIT_SUCCESS);
}

int main () {

    int PID_klienta;
    char string[DLUGOSC_KOMUNIKATU];
    int liczba1;
    int liczba2;
    char operator;
    int wynik;
    char wynik_s[DLUGOSC_KOMUNIKATU];
    mqd_t kolejka_desk;
    mqd_t odpowiedz;

    const double max_dlugosc_czekania = 4.0;

    kolejka_desk = kolejka_utworz (KOLEJKA_NAZWA, O_RDONLY);

    {
        struct mq_attr atrybuty = kolejka_pobierz_atrybuty (kolejka_desk);
        printf ("Utworzono kolejkę \"%s\" deskryptor %d o atrybutach:\n", KOLEJKA_NAZWA, kolejka_desk);
        printf ("mq_flags: = %ld\n", atrybuty.mq_flags);
        printf ("mq_maxmsg: = %ld\n", atrybuty.mq_maxmsg);
        printf ("mq_msgsize: = %ld\n", atrybuty.mq_msgsize);
        printf ("mq_curmsgs: = %ld\n\n", atrybuty.mq_curmsgs);
    }

    if (atexit (wyjscie) != 0) {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    if (signal (SIGINT,sygnal_wyjscie) == SIG_ERR) {
        perror("Błąd signal");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    while (1) {

        // czytaj komunikat z kolejki
        kolejka_odbierz (kolejka_desk, string, NULL);

        sscanf(string, "%d %d%c%d", &PID_klienta, &liczba1, &operator, &liczba2);

        printf ("Odebrano zapytanie od %d - działanie %d %c %d\n", PID_klienta, liczba1, operator, liczba2);

        // wykonaj obliczenie

        if (operator == '+') {
            wynik = liczba1 + liczba2;
            sprintf (wynik_s, "%d", wynik);
        } else if (operator == '-') {
            wynik = liczba1 - liczba2;
            sprintf (wynik_s, "%d", wynik);
        } else if (operator == '*') {
            wynik = liczba1 * liczba2;
            sprintf (wynik_s, "%d", wynik);
        } else if (operator == '/') {
            wynik = liczba1 / liczba2;
            sprintf (wynik_s, "%d", wynik);
        } else {
            sprintf (wynik_s, "Błąd: nieznany operator");
        }

        // czekaj losową ilość czasu
        sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);

        // odtwórz kolejkę do nadania odpowiedzi
        sprintf (string, "/%d", PID_klienta);
        odpowiedz = kolejka_otworz (string, O_WRONLY);

        // odpowiedz
        printf ("Wysyłanie odpowiedzi %s do procesu %d\n", wynik_s, PID_klienta);
        kolejka_wyslij (odpowiedz, wynik_s, 1);
        kolejka_zamknij (odpowiedz);

    }
    
    kolejka_usun (KOLEJKA_NAZWA);

    printf ("\n\nSerwer: koniec procesu\n");

    return 0;

}