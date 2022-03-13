#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

/*
	Przyjmuję dwa argumenty i umożliwia obsłużenie sygnału używając jednej z trzech opcji (default, ignore, custom)
*/

void obsluga_niestandardowa(int sygnal) {
	
	extern const char * const sys_siglist[];
	
	// wypisywanie nazwy i numeru sygnału
	printf("\nWłasna obsługa sygnału\n");
	printf("Sygnał %s, %d\n", sys_siglist[sygnal], sygnal);
}

int main (int argc, char *argv[]) {
	
	// obsługa niepoprawnej ilość argumentów
	if (argc < 3) {
		printf("Błąd: Program uruchomiony ze zbyt małą ilością argumentów\n");
		exit(EXIT_FAILURE);
	} else if (argc > 3) {
		printf("Błąd: Program uruchomiony ze zbyt dużą ilością argumentów\n");
		exit(EXIT_FAILURE);
	}
	
	// wypisywanie PIDu procesu
	printf("PID procesu: %d\n", getpid());
	
	if (strcmp(argv[2], "ignore") == 0) {
		if (signal(atoi(argv[1]),SIG_IGN) == SIG_ERR) {
			perror("Funkcja signal ma problem z SIGINT");
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(argv[2], "default") == 0) {
		if (signal(atoi(argv[1]),SIG_DFL) == SIG_ERR) {
			perror("Funkcja signal ma problem z SIGINT");
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(argv[2], "custom") == 0) {
		if (signal(atoi(argv[1]),obsluga_niestandardowa) == SIG_ERR) {
			perror("Funkcja signal ma problem z SIGINT");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("Błąd: Niepoprawna opcja %s\n", argv[2]);
	}
	
	pause();
}