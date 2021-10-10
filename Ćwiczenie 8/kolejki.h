#ifndef KOLEJKI_H
#define KOLEJKI_H

#define KOLEJKA_NAZWA "/kolejka_komunikatow"
#define MAX_WIADOMOSCI 10
#define DLUGOSC_KOMUNIKATU 30

// utwórz nową kolejkę o podanej nazwie i flagach
mqd_t kolejka_utworz (const char *name, int oflag);
// otwórz już istniejącą kolejkę o podanej nazwie i z użyciem danych flag
mqd_t kolejka_otworz (const char *name, int oflag);
// wyślij komunikat do kolejki z podanym priorytetem
void kolejka_wyslij (mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio);
// odbierz komunikat z podanej kolejki
void kolejka_odbierz (mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio);
// zamknij nie używaną już kolejkę
void kolejka_zamknij (mqd_t mq_des);
// usun kolejkę o podanej nazwie
void kolejka_usun (const char *name);
// pobierz atrybuty kolejki
struct mq_attr kolejka_pobierz_atrybuty (mqd_t mq_des);

#endif