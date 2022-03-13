#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

/*
	Program inkrementator odczytuje plik numer.txt, inkrementuje zawartą w nim liczbę i zapisuje ją z powrotem do pliku
*/

// argumenty [0] nazwa_programu [1] ilosc_sekcji_krytycznych [2] plik_we_wy [3] nazwa_semafora [4] synchronizacja
int main (int argc, char *argv[]) {
	
	int odczyt;
	char bufor[100];
	char komunikat[200];
	int liczba;
	int ilosc_sekcji_krytycznych;
	sem_t *semafor;
	int wartosc_semafora;
	int plik;
	bool synchronizacja;
	const double max_dlugosc_czekania = 2.0;
	
	if (argc != 5) {
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		printf ("Wywołaj podprogram wpisując: %s ilosc_sekcji_krytycznych plik_we_wy nazwa_semafora czy_synchronizowac\n", argv[0]);
		_exit (EXIT_FAILURE);
	}
	
	// pobieranie danych z argumentów
	
	ilosc_sekcji_krytycznych = atoi(argv[1]);
	
	if (atoi (argv[4]) == 0) {
		synchronizacja = false;
	} else {
		synchronizacja = true;
	}
	
	if (synchronizacja) {
		semafor = otworz_semafor (argv[3]);
	}
	
	for (int i = 0; i < ilosc_sekcji_krytycznych; i++) {
		
		/* Wlasne sprawy */
		
		srand(time(NULL));
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);
		
		// opuść semafor
		if (synchronizacja) {
			wartosc_semafor(semafor, &wartosc_semafora);
			printf ("PID %d przed SK semafor: %d\n", getpid(), wartosc_semafora);
			opusc_semafor (semafor);
		}
		
		/* Sekcja krytyczna */
		
		if ((plik = open (argv[2], O_RDONLY, 0644)) == -1) {
			printf ("Błąd otwarcia pliku %s do odczytu", argv[2]);
			perror ("Błąd pliku");
			_exit (EXIT_FAILURE);
		}
		
		odczyt = read(plik, &bufor, 10);
		if (odczyt == -1) {
			printf("Błąd odczytu z pliku\n");
			_exit(EXIT_FAILURE);
		} else if (odczyt == 0) {
			break;
		} else {
			bufor [odczyt] = '\0';
			wartosc_semafor(semafor, &wartosc_semafora);
			sprintf (komunikat, "\tPID %d semafor %d odczytany numer: %s SK: %d", getpid(), wartosc_semafora, bufor, i);
			
			printf ("%s\n", komunikat);
		}
		
		if (close (plik) == -1) {
			perror ("Błąd zamknięcia pliku");
			exit (EXIT_FAILURE);
		}
		
		liczba = atoi (bufor);
		liczba++;
		sprintf (bufor, "%d", liczba);
		printf ("liczba %d", liczba);
		
		// czekaj losową ilość czasu
		sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);
		
		if ((plik = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
			printf ("Błąd otwarcia pliku %s do zapisu", argv[1]);
			perror ("Błąd pliku");
			_exit (EXIT_FAILURE);
		}
		
		if (write (plik, &bufor, strlen(bufor)) == -1){
			perror("Błąd write do pliku");
			_exit(EXIT_FAILURE);
		}
		
		if (close (plik) == -1) {
			perror ("Błąd zamknięcia pliku");
			exit (EXIT_FAILURE);
		}
		
		// podnieś semafor
		if (synchronizacja) {
			podnies_semafor (semafor);
			wartosc_semafor(semafor, &wartosc_semafora);
			printf ("PID %d po SK semafor: %d\n", getpid(), wartosc_semafora);
		}
		
		/* Reszta */
	}
	
	if (synchronizacja) {
		zamknij_semafor (semafor);
	}
	
	return 0;
}