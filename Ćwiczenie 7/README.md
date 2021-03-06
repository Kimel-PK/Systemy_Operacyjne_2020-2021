# ĆWICZENIE 7: Producent—Konsument: Pamięć Dzielona i Semafory

## Treść zadania

Przy pomocy pamięci dzielonej oraz semaforów standardu `POSIX` zaimplementować problem "producenta—konsumenta" z ćwiczenia 4 przedstawiony poniższym pseudokodem.

Zamiast potoku użyć N-elementowego bufora cyklicznego (tzn. po dojściu do końca bufora wracamy na jego początek) umieszczonego w pamięci dzielonej, gdzie elementem bufora jest pewna ustalona porcja bajtów.

Dostęp do wspólnego bufora synchronizować przy pomocy semaforów nazwanych standardu `POSIX`.

Programy producenta i konsumenta uruchamiać przez `exec` w procesach potomnych utworzonych przez `fork` w procesie macierzystym — proces ten powinien wcześniej utworzyć i zainicjować semafory i pamięć dzieloną, a po utworzeniu procesów potomnych zaczekać na ich zakończenie i zrobić odpowiednie porządki.

Podobnie jak w ćwiczeniu 6, usuwanie obiektu pamięci dzielonej oraz semaforów umieścić w funkcji rejestrowanej przez `atexit` oraz funkcji obsługi sygnału `SIGINT`.

Bufor jednostek towaru można zdefiniować jako tablicę dwuwymiarową i umieścić go wewnątrz struktury wraz z iteratorami dla producenta i konsumenta, np.

```cpp
#define NELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // liczba elementow bufora

// Segment pamieci dzielonej
typedef struct {
    char bufor[NBUF][NELE]; // Wspolny bufor danych
    int wstaw, wyjmij; // Pozycje wstawiania i wyjmowania z bufora
} SegmentPD;
```

Odwzorowując obszar pamięci dzielonej w wirtualną przestrzeń adresową procesu należy wykonać odpowiednie rzutowanie typu, np.

```cpp
SegmentPD *wpd = (SegmentPD *) mmap(NULL, sizeof(SegmentPD), PROT_READ, MAP_SHARED, des, 0);
```

Następnie, przy użyciu tak zdefiniowanego wskaźnika można wykonywać operacje na tym segmencie, np.

```cpp
wpd->wyjmij = (wpd->wyjmij + 1) % NBUF;
```

Podobnie jak dla semaforów, stworzyć własną bibliotekę funkcji do obsługi pamięci dzielonej.

- Z własnych bibliotek funkcji do obsługi semaforów i pamięci dzielonej stworzyć bibliotekę statyczną oraz bibliotekę dzieloną (ang. sharedlibrary);  
umieścić je w podkatalogu `./lib` (patrz przykład w StartSO).
- Podać w pseudokodzie uogólnienie rozwiązania tego problemu na przypadek wielu producentów i wielu konsumentów (kolejność przesyłanych porcji danych może być dowolna - dane potraktować tu jak np. wodę).

Przykład pseudokodu dla ćwiczenia 7:

```cpp
// Pseudokod dla problemu Producenta i Konsumenta z buforem cyklicznym.
// Wspolny bufor do przesylania danych znajduje sie w pamieci dzielonej.
// Dostep do bufora jest synchronizowany semaforami.

#define N ? // Rozmiar bufora

typdef struct { ... } Towar; // Definicja typu dla jednostek towaru
Towar bufor[N]; // Bufor mogacy pomiescic N jednostek towaru
int wstaw = 0, wyjmij = 0; // Pozycje wstawiania oraz wyjmowania towaru
    // z bufora (mozna umieścic w pamieci dzielonej)

semaphore PROD = N; // Semafor do wstrzymywania Producenta
semaphore KONS = 0; // Semafor do wstrzymywania Konsumenta

// Proces Producent
// ----------------
Towar towarProd;
while (1) {
    // Produkcja towaru
    P(PROD); // Opusc semafor Producenta
    bufor[wstaw] = towarProd; // Umiesc towar w buforze
    wstaw = (wstaw + 1) % N; // Przesun pozycje wstawiania o 1 dalej
    V(KONS); // Podniesc semafor Konsumenta
}

// Proces Konsument
// ----------------
Towar towarKons;
while (1) {
    P(KONS); // Opusc semafor Konsumenta
    towarKons = bufor[wyjmij]; // Umiesc towar w buforze
    wyjmij = (wyjmij + 1) % N; // Przesun pozycje wstawiania o 1 dalej
    V(PROD); // Podniesc semafor Producenta
    // Konsumpcja towaru
}
```

## Dodatkowe notatki

- Semafory i pamięć dzieloną tworzyć z flagą `O_EXCL`.
- Po utworzeniu semaforów wypisać ich adresy i wartości początkowe, a po utworzeniu pamięci dzielonej wypisać jej dekskryptor oraz rozmiar w bajtach.
- Producent i konsument niech wypiszą na początku adresy semaforów i deskryptor pamięci dzielonej, a potem w trakcie przesyłania danych niech wypisują wartości semaforów, bieżący indeks elementu bufora, liczbę wstawianych/pobieranych bajtów oraz przesyłany tekst.
- Rozmiary tekstu oraz bufora dobrać tak, aby producent i konsument wykonali kilka obiegów (co najmniej dwa) po buforze cyklicznym.
- Rozmiar elementu bufora powinien być większy niż 1 bajt, a liczba elementów większa od 1.
- Programy producenta i konsumenta uruchamiać przez `exec` w dwóch procesach potomnych tworzonych funkcją `fork()` przez proces macierzysty, który na początku powinien stworzyć semafory i pamięć dzieloną, poczekać na zakończenie swoich potomków, a następnie usunąć semafory i pamięć dzieloną.
- Nazwy semaforów, pamięci dzielonej oraz plików tekstowych przekazywać do producenta i konsumenta przez argumenty funkcji `exec`.
- Do czytania/pisania danych z/do pliku użyć funkcji `read()`/`write()` i przesyłać surowe bajty, a nie formatowany tekst (ang. `string`).
- Jako sygnał końca danych producent może zapisać do bufora znak `'\0'`, a konsument po jego odczytaniu zakończyć pracę.
- Stworzyć dwa oddzielne moduły z funkcjami dla semaforów oraz pamięci dzielonej (jeden moduł to plik nagłówkowy `.h` i plik źródłowy `.c` o tej samej nazwie rdzeniowej).
- Z obydwu powyższych modułów stworzyć jedną biblioteką statyczną o rozrzerzeniu `.a` oraz podobnie jedną bibliotekę dzieloną o rozszerzeniu `.so`.
- W pliku `Makefile` umieścić oddzielne uruchomienie programu dla biblioteki statycznej oraz dwa sposoby uruchomienia dla biblioteki dzielonej (patrz przykład w StartSO).
- Na końcu porównać pliki tekstowe producenta i konsumenta, np. wstawić polecenie `diff -s` w pliku `Makefile` po zakończeńczeniu działania programów.

Programy kompilować/linkować z flagami: `-Wall -std=gnu99 -pedantic`

## Opis programu

Program implementuje problem producenta i konsumenta z wykorzystaniem semaforów oraz pamięci dzielonej

Przesyłanie danych jest realizowane za pomocą bufora cyklicznego do którego dostęp jest synchronizowany za pomocą semaforów

## Zawartość

Pliki `.c`

- `program7.c program_producent program_konsument`  
Program główny tworzący semafory i pamięć dzieloną, producent i konsumet są podprocesami tego programu
- `producent.c semafor_producent semafor_konsument nazwa_pd plik_we`  
Odczytuje z pliku wejściowego dane i zapisuje je w pamięci dzielonej
- `konsument.c semafor_producent semafor_konsument nazwa_pd plik_wy`  
Odczytuje z segmentu pamięci dzielonej dane i zapisuje je do pliku

Plik `README` z instrukcjami

Plik `pseudokod.txt` z rozwiązaniem problemu z wieloma producentami i konsumentami

Plik `surowce.txt` z przykładowmi danymi

Pusty plik `skonsumowane.txt`

## Jak uruchomić programy

Aby uruchomić program, należy wykonać komendę:

```bash
make run7
```

Aby uruchomić program korzystając z biblioteki statycznej, należy wykonać komendę:

```bash
make run7s
```

Aby uruchomić program korzystając z biblioteki dzielonej (wersja make 1), należy wykonać komendę:

```bash
make run7d1
```

Aby uruchomić program korzystając z biblioteki dzielonej (wersja make 2), należy wykonać komendę:

```bash
make run7d2
```

Aby wyczyścić zawartość katalogu (usunąć zbędne pliki), należy wykonać:

```bash
make clean
```

W celu archiwizacji oraz kompresji katalogu należy wykonać:

```bash
make tar
```
