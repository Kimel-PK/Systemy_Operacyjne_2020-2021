#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*
	Przyjmuje cztery argumenty i uruchamia podprogram C2, a następnie wysyła sygnał do jego grupy procesów
*/

int main (int argc, char *argv[]) {
	
	int pidDziecka = 0;
	int pidGrupyDziecka = 0;
	
	// obsługa niepoprawnej ilość argumentów
	if (argc < 5) {
		printf("Błąd: Program uruchomiony ze zbyt małą ilością argumentów\n");
		exit(EXIT_FAILURE);
	} else if (argc > 5) {
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
			
			// przełączanie na programC2
			if (execl(argv[3], argv[3], argv[1], argv[2], argv[4], NULL) == -1) {
				perror("execl error");
				exit(EXIT_FAILURE);
			}
			
			break;
			
		default:
			/* akcja dla procesu macierzystego */
			
			sleep(1);
			
			pidGrupyDziecka = getpgid (pidDziecka);
			
			// printf("%d != %d\n", pidGrupyDziecka, getpgid(0));
			
			if (kill (-1 * pidGrupyDziecka, 0) == -1) {
				perror("dziecko nie istnieje");
				exit(EXIT_FAILURE);
			}
			
			if (kill (-1 * pidGrupyDziecka, atoi(argv[1]))) {
				perror ("kill error");
				exit(EXIT_FAILURE);
			}
	};
	
	sleep(1);
	
	if (strcmp(argv[2], "ignore") == 0) {
		printf ("Program zakończył się a nadal istnieją procesy zombie\n");
		printf ("Wysyłanie sygnału SIGKILL do grupy procesów zombie\n");
		kill (-1 * pidGrupyDziecka, SIGKILL);
	}
}