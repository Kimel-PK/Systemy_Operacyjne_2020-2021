#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// wypisz na ekran identyfikatory procesów z użyciem funkcji exec

int main (int argc, char *argv[]) {
	
	int stat_lock = 0;
	
	int i = 0;
	for (i = 0; i < 3; i++) {
		
		switch (fork ()) {
			case -1:
				perror("fork error");
				exit(1);
				
			case 0:
				/* akcja dla procesu potomnego */
				
				execl (argv[1], argv[1], NULL);
				perror("execl error");
				
				break;
				
			default:
				/* akcja dla procesu macierzystego, np. wywolanie funkcji wait */
				if (wait(&stat_lock) == -1) {
					perror ("wait error:");
					exit (1);
				}
		}
		
	}
	
	printf ("Macierzysty\n");
	execl (argv[1], argv[1], NULL);
	
}