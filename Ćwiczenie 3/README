# ĆWICZENIE 3: Wysyłanie i Obsługa Sygnałów

## Treść zadania

### Podpunkt (a)

Napisać program do obsługi sygnałów z możliwościami:

- (1) wykonania operacji domyślnej
- (2) ignorowania oraz
- (3) przechwycenia i własnej obsługi sygnału.

Do oczekiwania na sygnał użyć funkcji `pause`.

Uruchomić program i wysyłać do niego sygnały przy pomocy sekwencji klawiszy oraz przy pomocy polecenia `kill` z poziomu powłoki.

### Podpunkt (b)

Uruchomić powyższy program poprzez funkcję `exec` w procesie potomnym innego procesu i wysyłać do niego sygnały poprzez funkcję systemową kill z procesu macierzystego.

> Uwaga: Przed wysłaniem sygnału sprawdzić, czy proces istnieje (patrz podrozdział 3.2).

### Podpunkt (c)

W procesie macierzystym utworzyć proces potomny i sprawić, aby stał się liderem nowej grupy procesów (funkcja `setpgid`), a następnie uruchomić w nim kilka procesów potomnych wykonujących program do obsługi sygnałów.

Z pierwszego procesu macierzystego wysyłać sygnały do całej grupy procesów potomnych po uprzednim sprawdzeniu jej istnienia (jak wyżej).

Identyfikator tej grupy procesów uzyskać przy pomocy funkcji `getpgid`.

Proces będący liderem grupy procesów niech ignoruje sygnały, a na końcu czeka na zakończenie wszystkich swoich procesów potomnych i wypisuje ich status zakończenia zwracany przez funkcję `wait`.

Numer sygnału oraz opcję obsługi we wszystkich powyższych programach przekazywać za pomocą argumentów wywołania programu - sprawdzać ich liczbę i wypisywać odpowiedni komunikat w przypadku błędnego uruchomienia.

## Dodatkowe notatki

Podpunkt (a): jeden program - ustawia obsługę sygnału na 3 sposoby zgodnie z opcją podaną jako argument wywołania programu, a następnie czeka na sygnał (funkcja `pause()`); numer sygnału przekazywać jako argument wywołania programu; niech proces wypisze na ekranie swój PID, a funkcja do własnej obsługi sygnału jego numer i nazwę (można wstawić krótki `sleep`).

Podpunkt (b): dwa programy - pierwszy w procesie potomnym uruchamia program z podpunktu (a), po czy z procesu macierzystego wysyła do niego sygnał; w procesie macierzystym przed wywołaniem funkcji `kill()` wstawić funkcję `sleep()` z krótkim czasem uśpienia.

Podpunkt (c): trzy programy - pierwszy tworzy jeden proces potomny i uruchamia w nim program, który ustawia ignorowanie sygnału, staje się liderem swojej grupy procesów, a następnie tworzy kilka procesów potomnych, które uruchamiają program z podpunktu (a); pierwszy proces macierzysty, po krótkim czasie uśpienia (funkcja `sleep()`) wysyła sygnał do całej grupy procesów; procesy macierzyste po utworzeniu wszystkich swoich procesów potomnych powinny na nie poczekać (funkcja `wait()` lub `waitpid()`).

Programy kompilować/linkować z opcjami: `-Wall -std=c99 -pedantic`

> UWAGA: W nowych wersjach Linuksa użycie powyższych opcji kompilatora skutkuje ostrzeżeniem, że funkcja `kill()` jest niezadeklarowana - aby tego uniknąć, należy na początku pliku użyć makra preprocesora: `#define _POSIX_C_SOURCE 200112L`
>
> Aby uniknąć podobnych ostrzeżeń dla funkcji `getpid()` trzeba dodać makro: `#define _XOPEN_SOURCE 500`

## Zawartość

Pliki `.c`

- `programA.c sygnał opcja`  
Przyjmuję dwa argumenty i umożliwia obsłużenie sygnału używając jednej z trzech opcji default, ignore, custom)
- `programB.c sygnał opcja programA`  
Przyjmuje trzy argumenty, uruchamia programA jako trzeci argument i wysyła do niego sygnał z zewnątrz
- `programC.c sygnał opcja programC2 programA`  
Przyjmuje cztery argumenty i uruchamia podprogram C2, a następnie wysyła sygnał do jego grupy procesów
- `programC2.c sygnał opcja programA`  
Program pośredni, tworzy 3 podprocesy z użyciem programu A i czeka aż jego dzieci odbiorą sygnał od dziadka

Plik `README.txt` z instrukcjami

## Jak uruchomić programy

Aby uruchomić podpunkt A, należy wykonać komendę:

```bash
make SYGNAL=? OPCJA=? runA
```

> gdzie `SYGNAL` to numer sygnału, a opcja sposób obsłużenia `[default/ignore/custom]`

Aby uruchomić podpunkt B, należy wykonać komendę:

```bash
make SYGNAL=? OPCJA=? runB
```

> gdzie `SYGNAL` to numer sygnału, a opcja sposób obsłużenia `[default/ignore/custom]`

Aby uruchomić podpunkt C, należy wykonać komendę:

```bash
make SYGNAL=? OPCJA=? runC
```

> gdzie `SYGNAL` to numer sygnału, a opcja sposób obsłużenia `[default/ignore/custom]`

Aby wyczyścić zawartość katalogu (usunąć zbędne pliki), należy wykonać:

```bash
make clean
```

W celu archiwizacji oraz kompresji katalogu należy wykonać:

```bash
make tar
```
