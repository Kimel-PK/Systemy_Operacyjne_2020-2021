// Wlasne pliki naglowkowe
#include "funkcja.h"

// Standardowe pliki naglowkowe
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NGEN 100000  // Liczba generowanych punktow MC
 
/* 
   Prosty program do wyznaczania liczby pi metoda Monte Carlo
   oraz wyliczania calki z funkcji dwoch zmiennych metoda podstawowa MC.
   --------------------------------------------------------------------
   Autor: ...............,                           Krakow, 12.02.2021
   --------------------------------------------------------------------
*/ 
int main(int argc,char *argv[])
{
  long i, ir1, ir2, nn = NGEN, np = 0;
  double rr1, rr2, dlogi, delta, pi_dokl, pi_mc, sum = 0;

  printf("        Metoda Monte Carlo:\n"); 
  printf("        -------------------\n");
  printf("1) Wyznaczanie wartosci liczby pi. \n");
  printf("2) Wyliczanie calki funkcji dwoch zmiennych.\n");                   
  // Dokladna wartosc pi
  pi_dokl = acos(-1.0);
  printf("=============================================\n");
  printf("Dokladnie: pi = %lf\n",pi_dokl);    
  // Inicjalizacja generatora liczb losowych
  srand(1);
  // Generowanie liczb losowych i wyliczanie pi metoda MC
  for (i = 1; i <= nn; ++i)
    {
      ir1 = rand();
      ir2 = rand();
      rr1 = ( (double) ir1 )/RAND_MAX;
      rr2 = ( (double) ir2 )/RAND_MAX;
      if (rr1*rr1 + rr2*rr2 <= 1.0)
	np++;
      // Wydruki kontrolne
      dlogi = log10(1.0*i);
      delta = dlogi - floor(dlogi);
      if (!delta)
	{
	  pi_mc = 4.0*np/i;
	  printf("Metoda MC: pi = %lf\t i = %8ld\n",pi_mc,i);    
	}
      // Liczenie calki metoda podstawowa MC
      sum += xy(rr1,rr2);
    }
  printf("Dokladnie: pi = %lf\n",pi_dokl);    
  printf("=============================================\n");
  printf("Calka funcji x*y na [0,1]x[0,1]\n");
  printf("-> Dokladnie: 0.25\n");
  printf("-> Metoda MC: %lf\n",sum/nn);
  printf("=============================================\n");
  return 0;
}

