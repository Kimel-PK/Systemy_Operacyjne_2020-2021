#ifndef DZIELONA_H
#define DZIELONA_H

int stworz_PD (const char *name);
int otworz_PD (const char *name);
void ustaw_rozmiar_PD (int fd, off_t length);
void zamknij_PD (int fd);
void usun_PD (const char *name);
void *odwzoruj_PD (int fd, size_t length);
void usun_odwzorowanie_PD (void *addr, size_t length);

#endif