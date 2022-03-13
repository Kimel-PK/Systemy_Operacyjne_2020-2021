#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

/*
	Program pośredni, tworzy 3 podprocesy z użyciem programu A i czeka aż jego dzieci odbiorą sygnał od dziadka
*/

int main (int argc, char *argv[]) {
	
	// obsługa niepoprawnej ilość argumentów
	if (argc < 4) {
		printf("Błąd: Program uruchomiony ze zbyt małą ilością argumentów\n");
		exit(EXIT_FAILURE);
	} else if (argc > 4) {
		printf("Błąd: Program uruchomiony ze zbyt dużą ilością argumentów\n");
		exit(EXIT_FAILURE);
	}
	
	int stat_lock = 0;
	
	setpgid (0,0);
	printf("PID podprocesu: %d\n", getpgrp());
	
	for (int i = 0; i < 3; i++) {
		
		switch (fork ()) {
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				/* akcja dla procesu wnuka */
				
				// przełączanie na programA
				if (execl(argv[3], argv[3], argv[1], argv[2], NULL) == -1) {
					perror("execl error");
					exit(EXIT_FAILURE);
				}
				
				perror("execl error");
				exit(EXIT_FAILURE);
				
				break;
				
			default:
				/* akcja dla procesu dziecka */
				
				break;
		};
	}
	
	if (signal(atoi(argv[1]),SIG_IGN) == SIG_ERR) {
		perror("Funkcja signal ma problem z SIGINT");
		exit(EXIT_FAILURE);
	}
	
	int pidProcesu;
	
	for (int i = 0; i < 3; i++) {
		if ((pidProcesu = wait(&stat_lock)) == -1) {
			perror ("wait error");
			exit(EXIT_FAILURE);
		}
		printf("Status zakończenia procesu %d: %d\n", pidProcesu, stat_lock);
	}
	
}