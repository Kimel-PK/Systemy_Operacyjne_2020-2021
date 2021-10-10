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

/* polecenie zadania

    Przy pomocy potoków nienazwanych systemu UNIX zaimplementować problem "Producenta i konsumenta".
    Dla zademonstrowania,że niedoszlo do utraty ani zwielokrotnienia towaru, niech Producent pobiera "surowiec" (np. porcje bajtów) z pliku tekstowego 
    i wstawia go jako towar do potoku, a Konsument niech umieszcza pobrany z potoku towar w innym pliku tekstowym (porcje danych Producenta i Konsumenta 
    nie muszą być równe). Po zakończeniu dzialania programów (wyczerpaniu zasobów "surowca")oba pliki tekstowe powinny być identyczne (można to sprawdzić 
    poleceniem diff -s, które najlepiej umieścić w pliku Makefile po poleceniu uruchomienia programu). Oba procesy niech drukują odpowiednie komunikaty 
    na ekranie, w tym towar, który przesyłają. Do zasymulowania różnych szybkości dzialania programów użyć funkcji sleep, np. z losowym czasem usypiania. 
    Do czytania/pisania danych z/do pliku tekstowego, jak również wypisywaniaich na ekran użyć funkcji read i write.

    • Dane do potoku przesyłać/pobierać małymi porcjami (po kilka bajtów, nie wszystko naraz!) i wypisywać na ekranie dane przesyłane za każdym razem 
        producenta i konsumenta; w ogólności porcje danych producenta i konsumenta mogą być różne, dlatego powinny zostać zdefiniowane oddzielnie.
    • Nazwy plików danych i wyników przekazywać przez argumenty wywołania programu.
    • Do czytania/pisania danych z/do pliku użyć funkcji read() i write(). 
    • Do wypisywania danych na ekranie również użyć funkcji write() z odpowiednim deskryptorem.
    • Do symulowania różnych szybkości działania procesów użyć funkcji sleep() z losowym czasem usypiania generowanym np. przez funkcję rand()
        (patrz: man 3 rand)
    • UWAGA: Fukcją write() wpisywać liczbę faktycznie wczytanych przez read() bajtów (zwracaną prze nią).
    • Kompilacja/linkowanie z flagami: -Wall -std=c99 -pedantic

*/

// program symuluje problem producenta i konsumenta, dane przenoszone są pomiędzy dwoma plikami używając potoka z nierównym tempem

int main (int argc, char *argv[]) {

    char bufor[1024];
    char komunikat[1038];
    int plik;
    int filedes[2];
    int odczyt;
    const size_t rozmiarDanychProducent = 20; // nie może być większy niż 1024
    const size_t rozmiarDanychKonsument = 10; // nie może być większy niż 1024
    int stat_lock;
    const double maxDlugoscCzekania = 2.0;

    // sprawdzenie poprawności argumentów
    if (argc != 3) {
        printf ("Błąd: niepoprawna liczba argumentów!\n");
        printf ("Wywołaj program wpisując: %s plik_we plik_wy\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    if (pipe(filedes) == -1) {
        perror("Błąd potoku");
        exit (EXIT_FAILURE);
    }

    srand(time(NULL));

    switch (fork ()) {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            /* akcja dla procesu konsumenta */

            if (close (filedes[1]) == -1) { // zamykamy nieużywany zapis
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }

            if ((plik = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
                printf ("Błąd otwarcia pliku %s do zapisu", argv[2]);
                perror ("Błąd pliku");
                exit (EXIT_FAILURE);
            }

            // zapisywanie skosumowanych produktów do pliku
            while (1) {

                // czekaj losową ilość czasu
                sleep ((double)(rand() % (int)(maxDlugoscCzekania * 100)) / 100);

                odczyt = read(filedes[0], &bufor, rozmiarDanychKonsument);
                if (odczyt == -1) {
                    printf("Błąd odczytu z potoku\n");
                    exit(EXIT_FAILURE);
                } else if (odczyt == 0) {
                    break;
                } else {
                    write (plik, &bufor, odczyt);
                    bufor [odczyt] = '\0';
                    sprintf (komunikat, "%s%s%s", "Konsumuje <= ", bufor, "\n");
                    write (STDOUT_FILENO, komunikat, strlen(komunikat));
                }
            }

            if (close (plik) == -1) {
                perror ("Błąd zamknięcia pliku wyjścia");
                exit (EXIT_FAILURE);
            }

            if (close (filedes[0]) == -1) {
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }

            break;

        default:
            /* akcja dla procesu producenta */

            if (close (filedes[0]) == -1) { // zamykamy nie używany odczyt
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }

            if ((plik = open (argv[1], O_RDONLY, 0644)) == -1) {
                printf ("Błąd otwarcia pliku %s do odczytu", argv[1]);
                perror ("Błąd pliku");
                exit (EXIT_FAILURE);
            }

            // zapisywanie wyprodukowanych produktów do potoku
            while (1) {

                // czekaj losową ilość czasu
                sleep ((double)(rand() % (int)(maxDlugoscCzekania * 100)) / 100);

                odczyt = read(plik, &bufor, rozmiarDanychProducent);
                if (odczyt == -1) {
                    printf("Błąd odczytu z pliku\n");
                    exit(EXIT_FAILURE);
                } else if (odczyt == 0) {
                    break;
                } else {
                    write (filedes[1], &bufor, odczyt);
                    bufor [odczyt] = '\0';
                    sprintf (komunikat, "%s%s%s", "Produkuje => ", bufor, "\n");
                    write (STDOUT_FILENO, komunikat, strlen(komunikat));
                }
            }

            if (close (plik) == -1) {
                perror ("Błąd zamknięcia pliku wyjścia");
                exit (EXIT_FAILURE);
            }

            if (close (filedes[1]) == -1) {
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }

            if (wait (&stat_lock) == -1) {
                perror ("Błąd wait");
                exit (EXIT_FAILURE);
            }

            break;

    }

    return 0;

}