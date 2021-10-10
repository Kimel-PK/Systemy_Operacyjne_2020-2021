#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

/*

    Przyjmuje trzy argumenty, uruchamia programA jako trzeci argument i wysyła do niego sygnał z zewnątrz

*/

int main (int argc, char *argv[]) {

    int pidDziecka = 0;

    // obsługa niepoprawnej ilość argumentów
    if (argc < 4) {
        printf("Błąd: Program uruchomiony ze zbyt małą ilością argumentów\n");
        exit(EXIT_FAILURE);
    } else if (argc > 4) {
        printf("Błąd: Program uruchomiony ze zbyt dużą ilością argumentów\n");
        exit(EXIT_FAILURE);
    }

    printf("PID procesu: %d\n", getpid());

    switch (pidDziecka = fork ()) {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            /* akcja dla procesu potomnego */

            // przełączanie na programA
            if (execl(argv[3], argv[3], argv[1], argv[2], NULL) == -1) {
                perror("execl error");
                exit(EXIT_FAILURE);
            }

            break;

        default:
            /* akcja dla procesu macierzystego */

            sleep(1);

            if (kill(pidDziecka, 0) == -1) {
                perror("dziecko nie istnieje");
                exit(EXIT_FAILURE);
            }

            if (kill(pidDziecka, atoi(argv[1])) == -1) {
                perror ("kill error");
                exit(EXIT_FAILURE);
            }

    }

    if (strcmp(argv[2], "ignore") == 0) {
        sleep (1);

        printf ("Program zakończył się a nadal istnieją procesy zombie\n");
        printf ("Wysyłanie sygnału SIGKILL do procesu zombie\n");
        kill (pidDziecka, SIGKILL);

    }

}