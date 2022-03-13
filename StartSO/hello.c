/* 
 Program wypisuje powitanie w losowo wybranych miejscach na ekranie.
 ----------------------------------------------------------------------
 Autor: ...............,                             Krakow, 12.02.2021
 ----------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define XMAX 45      // Maksymalna liczba kolumn ekranu 
#define YMAX 20      // Maksymalna liczba wierszy ekranu
#define NMAX  5      // Liczba wypisan na ekran

/*
	=========================================================================
	Ustawienie pozycji kursora w punkcie o wspolrzednych (x,y) na ekranie,
	gdzie x - liczba kolumn (od lewej), y - liczba wierszy (od gory).
	Sekwencja \033[2K powoduje wymazanie poprzedniego napisu w danym wierszu.
	=========================================================================
*/
void gotoxy(unsigned x, unsigned y)
{
	printf("\033[%d;%dH\033[2K", y, x);
}

// Przyklad funkcji do rejestracji przez atexit() w celu wywolania jej
// przez funkcje exit() lub instrukcje return funkcji main().
void koniec(void)
{
	printf("\n>>> Koniec procesu - porzadki zrobione!\n\n");
}

int main()
{

	// Rejestracja funkcji koniec() do wywolania przez exit()
	if (atexit(koniec) != 0) {
		perror("Error in call to atexit() function");
		exit(EXIT_FAILURE);
	}
	
	printf("\033[5;7m");     // Wlacz migotanie i odwrotny obraz
	printf("    ---- Nacisnij klawisz [Enter], aby wystartowac! ----   ");
	getchar();
	printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania

	// Wyczysc ekran
	if (system("clear") == -1) {
		perror("Error in call to system() function");
		exit(EXIT_FAILURE);
	}
	srand(123);              // Zainicjuj generator liczb losowych
	printf("\033[1;4m");     // Wlacz pogrubienie i podkreslenie

	// Powtarzaj wypisywanie NMAX razy
	for (int i = 0; i < NMAX; i++) {
		// Wybieraj losowo wspolrzedne kursora (x,y)
		int x = 1 + (int) ( 1.0*XMAX*rand()/(RAND_MAX + 1.0) );
		int y = 1 + (int) ( 1.0*YMAX*rand()/(RAND_MAX + 1.0) );
		gotoxy(x, y);
		printf("Witaj na kursie \"Systemy operacyjne\"!\n");
		sleep(1);              // Poczekaj chwile
	} // for

	printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
	gotoxy(0, YMAX+1);

	return 0;
}