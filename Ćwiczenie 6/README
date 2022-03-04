# ĆWICZENIE 6: Wzajemne Wykluczanie dla Procesów: Semafory

## Treść zadania

Przy pomocy semaforów nazwanych standardu `POSIX` zaimplementować zadanie wzajemnego wykluczania dla procesów podane w pseudokodzie na końcu podrozdziału 5.1.

Czas operacji na wspólnym zasobie symulować używając np. funkcji `sleep`.

Dla demonstracji poprawności działania programu użyć odpowiednich komunikatów wypisywanych przez poszczególne procesy przed, w trakcie i po sekcji krytycznej oraz funkcji podającej wartość semafora.

Pamiętać o zainicjowaniu semafora odpowiednią wartością zaraz po jego utworzeniu.

- Stworzyć własną bibliotekę prostych w użyciu funkcji do tworzenia, otwierania, uzyskiwania wartości, operowania, zamykania i usuwania semafora — korzystających z odpowiednich funkcji systemowych/bibliotecznych i zawierających obsługę błędów.
- Napisać specjalny program do powielania procesów realizujących wzajemne wykluczanie - w oparciu o funkcje fork i exec (nazwę programu do inicjowania procesów, liczbę procesów oraz liczbę sekcji krytycznych/prywatnych każdego procesu przekazywać przez argumenty programu `powielacza`).
  
  > Program ten powinien na początku utworzyć i zainicjować semafor, a na końcu - kiedy wszystkie jego procesy potomne zakończą swoje działanie — usunąć go.
- Semafor usuwać w funkcji rejestrowanej przez funkcję `atexit` (zwrócić uwagę, kiedy należy wywołać funkcję `exit`, a kiedy `_exit`).  
Dodać również możliwość usuwania semafora w funkcji obsługi sygnału `SIGINT`, na wypadek gdyby program trzeba było zakończyć sekwencją klawiszy `Ctrl-C`.
- W celu weryfikacji poprawności wzajemnego wykluczania procesów niech program `powielacz` na samym początku stworzy plik tekstowy `numer.txt` i wpisze w nim numer o wartości 0 (zero), a program implementujący wzajemne wykluczanie w swojej sekcji krytycznej odczytuje wartość zapisanego w tym pliku numeru, następnie zwiększa go o `1` i po losowej (np. funkcja `rand`) chwili czasu zapisuje z powrotem do pliku.
Po zakończeniu działania wszystkich procesów realizujących wzajemne wykluczanie proces `powielacz` powinien sprawdzić poprawność końcowego numeru zapisanego w pliku i wypisać odpowiedni komunikat.

> Sprawdzić, jaka będzie końcowa wartość numeru bez użycia sekcji krytycznej.

## Dodatkowe notatki

- Semafor tworzyć z flagą `O_EXCL`.
- W programie powielaczu wypisać adres i wartość początkową stworzonego semafora.
- W programie do wzajemnego wykluczania wypisywać PID procesu oraz wartość semafora przed, wewnątrz i po sekcji krytycznej, a także numer wykonywanej sekcji krytycznej.
- Plik `numer.txt` najlepiej najpierw otworzyć w trybie tylko do odczytu, przeczytać zapisany w nim numer, zamknąć go, a następnie po zwiększeniu numeru o 1 otworzyć go ponownie w trybie do zapisu, wpisać do niego nową wartość numeru i zamknąć go - to wszystko powinno odbywać się w sekcji krytycznej programu.
- Po odczytaniu numeru z pliku wypisać go na ekranie, a po zakończeniu wszystkich procesów realizujących wzajemne wykluczanie wypisać jego końcową wartość i porównać z wartością oczekiwaną w przypadku poprawnej synchronizacji procesów.
- Wywołanie funkcji `sleep()` (np. z losowym czasem) wstawić w sekcji krytycznej między odczytem a zapisem numeru z/do pliku, a także przed wejściem do sekcji krytycznej.
- Do odczytu/zapisu numeru można używać niskopoziomowych funkcji WE/WY `read()` i `write()` lub funkcji formatowanego WE/WY.
- Przy wypisywaniu informacji w sekcji krytycznej na ekranie użyć dodatkowego odstępu po lewej stronie, np. tabulatora, by łatwiej było ją odróżnić od sekcji prywatnej procesu.
- Wyłączyć synchronizację semaforem (np. wykomentować odpowiednie operacje) i sprawdzić końcową wartość numeru (powinna być mniejsza od tej z użyciem semafora).

Kompilować/linkować programy z flagami: `-Wall -std=c99 -pedantic`

## Opis programu

Program implementuje problem jednoczesnego korzystania z zasobu współdzielonego przez kilka procesów

Do pliku `numer.txt` wpisywana jest liczba 0 następnie procesy potomne odczytują tą wartość, inkrementują ją i zapisują ponownie do pliku

## Zawartość

Pliki `.c`

- `powielacz.c nazwa_podprogramu ilosc_inkrementatorow ilosc_sekcji_krytycznych plik_we_wy nazwa_semafora czy_synchronizowac`  
Program główny przedstawiający problem jednoczesnego korzystania z zasobu współdzielonego przez X procesów z X sekcjami krytycznymi
- `inkrementator.c ilosc_sekcji_krytycznych plik_we_wy nazwa_semafora czy_synchronizowac`  
Odczytuje z pliku `numer.txt` liczbę, inkrementuje ją i zapisuje z powrotem do pliku

Plik `README.txt` z instrukcjami

Plik `numer.txt`

## Jak uruchomić programy

Aby uruchomić program, należy wykonać komendę:

```bash
make run6
```

Aby wyczyścić zawartość katalogu (usunąć zbędne pliki), należy wykonać:

```bash
make clean
```

W celu archiwizacji oraz kompresji katalogu należy wykonać:

```bash
make tar
```
