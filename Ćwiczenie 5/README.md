# ĆWICZENIE 5: Producent-Konsument: Potoki Nazwane

## Treść zadania

Przy pomocy potoków nazwanych systemu UNIX zaimplementować problem "Producenta i Konsumenta” z ćwiczenia 4.

### Podpunkt (a)

Utworzyć potok FIFO z poziomu programu, a następnie uruchomić procesy Producenta i Konsumenta w tym samym programie (w procesie macierzystym i potomnym lub w dwóch potomnych).

> Potok usuwać w funkcji zarejestrowanej przez `atexit`.

### Podpunkt (b)

Sprawdzić, że potoki FIFO działają dla niezależnych procesów przez utworzenie potoku FIFO z linii komend oraz uruchomienie procesów Producenta i Konsumenta niezależnie z poziomu powłoki, np. w różnych terminalach — można użyć polecenia:

```bash
xterm -hold -title nazwa okna -e nazwa_programu & ...
```

dla każdego z tych procesów w pliku Makefile (jak też tworzenie/usuwanie potoku).

## Dodatkowe notatki

- Implementacja problemu "Producent-konsument" jak w ćwiczeniu 4.
- Najlepiej zaimplementować "producenta" i "konsumenta" w dwóch oddzielnych programach (funkcjach `main()`) - każdy z nich niech przez argumenty wywołania pobiera nazwę potoku oraz nazwę odpowiedniego pliku tekstowego; potok nazwany - tak jak plik - przed użyciem należy otworzyć funkcją `open()`, a po użyciu zamknąć funkcją `close()`.
- W punkcie (a) napisać dodatkowy program, który utworzy potok nazwany, następnie przy pomocy funkcji `fork()` utworzy dwa procesy potomne, w których przy użyciu wywołania `exec` uruchomi odpowiednio programy "producenta" i "konsumenta", a na końcu poczeka na ich zakończenie i usunie potok (nazwy plików wykonawczych dla `exec` przekazywać przez argumenty wywołania programu).
- Potok usuwać w funkcji zarejestrowanej przez funkcję `atexit()`. Zwrócić uwagę na to, gdzie należy wywołać funkcję `exit()`, a gdzie `_exit()` - by nie usuwać potoku, który nie został jeszcze utworzony lub nie usuwać go więcej niż raz! Dodatkowo, można dodać obsługę sygnału `SIGINT`, która będzie usuwać potok - na wypadek gdyby program trzeba było zakończyć sekwencją klawiszy `Ctrl-C`.
- Nazwy plików danych i wyników oraz nazwę potoku przekazywać przez argumenty wywołania programu.
- W punkcie (b) potok nazwany utworzyć z poziomu powłoki, następnie uruchomić programy "producenta" i "konsumenta" z różnych terminali, a na końcu z poziomu powłoki usunąć potok.

  Najlepiej wszystkie te polecenia umieścić w pliku Makefile, np. programy uruchomić za pomocą xterm:

  ```bash
  xterm -hold -title PRODUCENT -e ./producent.x mojfifo dane.txt & xterm -hold -title KONSUMENT -e ./konsument.x mojfifo wyniki.txt
  ```
  
- Programy "producent" i "konsument" niech wypisują na ekranie komunikaty o przesyłanych danych, jak w ćwiczeniu 4; na końcu sprawdzić poprawność wykonania programów przez porównanie pliku danych "producenta" z plikiem wyników "konsumenta", np. przy pomocy polecenia `diff -s`

> UWAGA: Fukcją `write()` wpisywać liczbę faktycznie wczytanych przez `read()` bajtów (zwracaną prze nią).

Programy kompilować/linkować z flagami: `-Wall -std=c99 -pedantic`

## Opis programu

Program przedstawia implementacje problemu producenta i konsumenta z wykorzystywaniem potoku nazwanego

- Podpunkt A używa do tego celu procesów potomnych
- W podpunkcie B podprogramy uruchamiane są jako procesy nie powiązane za sobą, a tworzenie i usuwanie potoku zrealizowane jest poleceniami powłoki

## Zawartość

Pliki `.c`

- `programA.c prog_producent prog_konsument plik_we plik_wy potok`  
Przyjmuje 5 argumentów, symuluje problem producenta i konsumenta z wykorzystaniem potoku nazwanego i procesów potomnych
- `producent.c plik_we potok`  
Przyjmuje dwa argumenty, pobiera dane z plik_we i przekazje je do wskazanego potoku
- `konsument.c plik_wy potok`  
Przyjmuje dwa argumenty, pobiera dane z potoku i zapisuje je w plik_wy

Plik `README.txt` z instrukcjami

Plik `surowce.txt` z przykładowymi danymi

Pusty plik `skonsumowane.txt`

## Jak uruchomić programy

Aby uruchomić podpunkt A, należy wykonać komendę:

```bash
make runA
```

Aby uruchomić podpunkt B, należy wykonać komendę:

```bash
make runB
```

Aby wyczyścić zawartość katalogu (usunąć zbędne pliki), należy wykonać:

```bash
make clean
```

W celu archiwizacji oraz kompresji katalogu należy wykonać:

```bash
make tar
```
