#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include "kolejki.h"

mqd_t serwer;

void wyjscie(void) {
    kolejka_zamknij (serwer);
}

void sygnal_wyjscie(int signal) {
    printf ("\nSygnał przerwania, zamykanie kolejki\n");
    exit(EXIT_SUCCESS);
}

int main () {

    char kolejka_odpowiedz_nazwa[10];
    mqd_t kolejka_odpowiedz;
    char odczyt[DLUGOSC_KOMUNIKATU];
    char string[DLUGOSC_KOMUNIKATU+10];
    const double max_dlugosc_czekania = 4.0;

    sprintf (kolejka_odpowiedz_nazwa, "/%d", getpid());

    // zaczekaj chwile zanim serwer się uruchomi
    sleep (1);

    serwer = kolejka_otworz (KOLEJKA_NAZWA, O_WRONLY);
    
    {
        struct mq_attr atrybuty = kolejka_pobierz_atrybuty (serwer);
        printf ("Otworzono kolejkę \"%s\" o deskryptorze %d\n", KOLEJKA_NAZWA, serwer);
        printf ("mq_flags: = %ld\n", atrybuty.mq_flags);
        printf ("mq_maxmsg: = %ld\n", atrybuty.mq_maxmsg);
        printf ("mq_msgsize: = %ld\n", atrybuty.mq_msgsize);
        printf ("mq_curmsgs: = %ld\n\n", atrybuty.mq_curmsgs);
    }

    if (atexit (wyjscie) != 0) {
        perror("atexit error");
        _exit(EXIT_FAILURE);
    }

    if (signal (SIGINT,sygnal_wyjscie) == SIG_ERR) {
        perror("Błąd signal");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    // czekaj losową ilość czasu
    sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);

    while (1) {

        // wpisz działanie
        printf ("Wpisz działanie\n");
        if (scanf ("%s", odczyt) == EOF) {

            printf ("\n========================================================\n");
            printf ("Koniec odczytu, teraz możesz bezpiecznie zamknąć konsolę\n");
            exit(EXIT_SUCCESS);
        }
        // dopisz PID do komunikatu
        sprintf(string, "%d %s", getpid(), odczyt);

        // wyślij zapytanie na serwer
        kolejka_wyslij(serwer, string, 1);
        printf ("\nWysłano zapytanie do serwera: %s\n", string);

        // utwórz kolejkę do odebrania odpowiedzi
        kolejka_odpowiedz = kolejka_utworz (kolejka_odpowiedz_nazwa, O_RDONLY);

        // oczekuj na odpowiedź z serwera
        printf ("Oczekiwanie na odpowiedź z serwera\n");
        kolejka_odbierz (kolejka_odpowiedz, string, NULL);
        printf ("Odpowiedź z serwera: %s\n\n", string);

        // zamknij i usuń kolejkę do odebrania odpowiedzi
        kolejka_zamknij (kolejka_odpowiedz);
        kolejka_usun (kolejka_odpowiedz_nazwa);

        // czekaj losową ilość czasu
        sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);

    }

    // zamknij kolejkę serwera
    kolejka_zamknij (serwer);
    
    printf ("\n\nKlient: koniec procesu\n");

    return 0;

}