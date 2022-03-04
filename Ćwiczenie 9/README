# ĆWICZENIE 9: Wzajemne wykluczanie dla Wątków: Muteksy

## Treść zadania

Przy pomocy muteksów zaimplementować zadanie wzajemnego wykluczania dla wątków.

Do demonstracji działania programu można użyć sekwencji sterujących konsoli (patrz np. plik `hello.c` w katalogu StartSO).

Niech na przykład wątek wykonując swoją sekcję prywatną wypisuje odpowiedni komunikat po lewej stronie okna konsoli, natomiast będąc w sekcji krytycznej drukuje informacje po prawej stronie (w tym samym wierszu).

Każdy wątek może kilka razy powtarzać powyższy cykl.

Przy poprawnie zrealizowanym zadaniu wzajemnego wykluczania, po prawej stronie okna konsoli w danym momencie powinien zgłaszać się co najwyżej jeden wątek, pozostałe natomiast powinny zgłaszać się po lewej stronie.

Do zademonstrowania operacji na zasobie dzielonym użyć np. wspólnej (globalnej) zmiennej licznikowej, zainicjowanej wartością 0.

Niech każdy z wątków na początku sekcji krytycznej przypisuje jej wartość swojemu prywatnemu licznikowi, następnie zwiększa wartość tego prywatnego licznika o 1, a po pewnym czasie (użyć np. funkcji `sleep`) przypisuje jego wartość wspólnemu licznikowi.

Sprawdzić, czy po zakończeniu działania wszystkich wątków wartość tego wspólnego licznika jest taka jaka powinna być.

## Dodatkowe notatki

- Liczbę wątków oraz liczbę sekcji krytycznych/prywatnych wątku przekazywać przez argumenty wywołania programu.
- Wątek główny powinien utworzyć muteks i zainicjować go, uruchomić wątki realizujące wzajemne wykluczanie, a następnie poczekać na ich zakończenie.
- Na początku wypisać na ekranie adres utworzonego muteksu oraz numery i identyfikatory wątków.
- W trakcie działania wątków wypisywać numer wątku i numer kolejny jego sekcji prywatnej (po lewej stronie ekranu) oraz jego sekcji krytycznej (po prawej stronie ekranu); można też wypisywać aktualną wartość licznika globalnego
- Po prawej stronie ekranu powinien w danej chwili być widoczny tylko jeden wątek w swojej sekcji krytycznej, a po lewej stronie pozostałe wątki w swoich sekcjach prywatnych.
- Wstawić funkcję `sleep()` z losowym czasem uśpienia między pobraniem wartości licznika globalnego o jego uaktualnieniem.
- Losowe uśpienie wątku wstawić również w sekcji prywatnej.
- Po zakończeniu działania wątków usunąć muteks i wypisać wartość licznika globalnego oraz jego wartość oczekiwaną dla poprawnej synchronizacji.

## Opis programu

Program implementuje problem wzajemnego wykluczania wątków standardu POSIX z użyciem muteksów, globalna liczba jest kolejno inkrementowana przez wątki, muteks zabezpiecza przed jednoczesnym dostępem dwóch wątków do zasobu dzielonego.

## Zawartość

Pliki `.c`

- `cwiczenie9.c`  
Uruchamia podaną ilość wątków o podanej ilości sekcji krytycznych.
Każdy wątek uzyskuje dostęp do zmiennej globalnej i zwiększa jej wartość o 1.
Na koniec sprawdzana jest poprawność synchronizacji wątków
- `watki.c, watki.h`  
Biblioteka z funkcjami potrzebnymi do obsługi wątków.

Plik `README` z instrukcjami

## Jak uruchomić programy

Aby uruchomić program, należy wykonać komendę:

```bash
make run9
```

Aby wyczyścić zawartość katalogu (usunąć zbędne pliki), należy wykonać:

```bash
make clean
```

W celu archiwizacji oraz kompresji katalogu należy wykonać:

```bash
make tar
```
