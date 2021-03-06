# ĆWICZENIE 8: Klient-Serwer: Kolejki Komunikatów

## Treść zadania

Proces klienta wysyła do procesu serwera żądanie wykonania działania arytmetycznego na dwóch liczbach postaci: liczba o liczba, gdzie operator o należy do `{+,-,*,/}`, np. `2 + 3`.
Serwer wykonuje odpowiednie działanie i odsyła wynik do klienta.

Klient odbiera ten wynik i wypisuje go na ekranie.

Posługując się mechanizmem kolejek komunikatów standardu `POSIX` zaimplementować powyższe zadanie typu klient-serwer z możliwością obsługi przez serwerawielu klientów naraz.

Niech serwer utworzy kolejkę komunikatów w trybie do odbierania o nazwie zdefiniowanej we wspólnym pliku nagłówkowym włączanym w plikach źródłowych programów serwera i klienta.

Do tej kolejki klient będzie wysyłał swoje komunikaty, a serwer będzie je z niej odbierał.

Klient z kolei niech utworzy kolejkę komunikatów w trybie do odbierania o nazwie `/PID`, gdzie PID jest jego identyfikatorem procesu PID, np. `/17895` (do utworzenia tej nazwy użyć np. funkcji `sprintf`).

Następnie niech klient otworzy kolejkę serwera w trybie do nadawania komunikatów i w pętli wczytuje z klawiatury żądane działanie (np. używając funkcji `fgets`), tworzy komunikat umieszczając na początku swój PID, a po nim wczytane wyrażenie (np. przy pomocy funkcji `sprintf`), po czym wysyła taki komunikat do kolejki serwera.

Pętlę można zakończyć znakiem końca pliku `EOF` (z klawiatury wysyła się go sekwencją klawiszy `Ctrl+D`), po czym klient powinien zamknąć i usunąć własną kolejkę oraz zamknąć kolejkę serwera - czynności te umieścić w funkcji rejestrowanej przez `atexit` oraz w obsłudze sygnału `SIGINT`.

Serwer niech działa w pętli nieskończonej (proces `demon`), próbując odbierać komunikaty ze swojej kolejki.

Po otrzymaniu komunikatu od klienta, serwer powinien odczytać z niego PID klienta (np. funkcją `atoi`) i otworzyć kolejkę klienta w trybie do nadawania komunikatów o nazwie postaci `/PID` (użyć np. funkcji `sprintf`).

Następnie z komunikatu powinien odczytać odpowiednie działanie (można użyć np. funkcji `sscanf`), wykonać je i odesłać wynik w komunikacie (użyć np. funkcji `sprintf`) do kolejki klienta, po czym zamknąć tę kolejkę.

Proces serwera można zakończyć np. sygnałem `SIGINT` (z klawiatury sekwencją klawiszy `Ctrl+C`), z tym że serwer powinien przechwycić ten sygnał i wykonać jego obsługę w postaci zamknięcia i usunięcia własnej kolejki komunikatów - czynności te umieścić w funkcji rejestrowanej przez `atexit`.

Niech procesy serwera i klienta wypisują na ekranie odpowiednie komunikaty, w szczególności atrybuty kolejek komunikatów zaraz po ich utworzeniu.

Uruchamiać każdy proces z innego terminala, np. użyć polecenia:

```bash
xterm -hold -title SERWER -bg red -e ./serwer.x &
xterm -hold -title KLIENT1 -bg green -e ./klient.x &
xterm -hold -title KLIENT2 -bg green -e ./klient.x &
...
```

w pliku `Makefile` do uruchomienia serwera i kilku klientów (więcej szczegółów można znaleźć w man `xterm`).

Podobnie jak dla semaforów i pamięci dzielonej, stworzyć własną bibliotekę funkcji do obsługi kolejek komunikatów

## Dodatkowe notatki

- Nazwę kolejki serwera najlepiej zdefiniować w pliku nagłówkowym włączanym w programach serwera i klienta.
- Na początku niech serwer i klient wypisują na ekranie nazwę, deskryptor i atrybuty utworzonej kolejki.
- Następnie niech klient w pętli (do końca pliku `EOF`, czyli `Ctrl+D` z klawiatury) wypisuje na ekranie prośbę o wpisanie z klawiatury odpowiedniego działania i wczytuje je.
- Serwer niech wypisuje na ekranie otrzymany komunikat oraz wynik wykonanego działania, a klient wynik otrzymany od serwera - sprawdzić, czy oba wyniki się zgadzają!
- W programach serwera oraz klienta wstawić funkcję `sleep()`, np. z losowym czasem, między odebraniem a wysłaniem komunikatu lub odwrotnie.

Użyć flag kompilatora: `-Wall -std=c99 -pedantic`

## Opis programu

Program implementuje działanie centralnego serwera, który wykonuje obliczenia zlecone mu przez podłączonych do niego klientów.

Przesyłanie danych jest realizowane za pomocą kolejek komunikatów

## Zawartość

Pliki `.c`

- `serwer.c`  
Program serwera, który czeka na komunikaty, wykonuje zawarte w nich działania i odsyła do odpowiednich procesów
- `klient.c`  
Ustanawia połączenie z serwerem, czeka aż uzytkownik wpiszę w konsole działanie po czym wysyła je w formie komunikatu do serwera i odbiera od niego wynik

Plik `README` z instrukcjami

## Jak uruchomić programy

Aby uruchomić program, należy wykonać komendę:

```bash
make run8
```

Aby wyczyścić zawartość katalogu (usunąć zbędne pliki), należy wykonać:

```bash
make clean
```

W celu archiwizacji oraz kompresji katalogu należy wykonać:

```bash
make tar
```
