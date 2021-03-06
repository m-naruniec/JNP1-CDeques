# C Deques


## Task description in Polish

Biblioteka standardowa języka C++ udostępnia bardzo przydatne kontenery (np.
map i deque), których nie ma w bibliotece C. Kontener deque (kolejka
dwustronna) jest alternatywą dla kontenera vector, pozwalającą na wstawianie
elementów na początku i na końcu w (amortyzowanym) czasie stałym.

Często potrzebujemy łączyć kod C++ z kodem spadkowym w C. Celem tego zadania
jest napisanie w C++ dwóch modułów obsługujących kolejki dwustronne ciągów
znaków, tak aby można ich było używać w C. Każdy moduł składa się z pliku
nagłówkowego (z rozszerzeniem h) i pliku z implementacją (z rozszerzeniem cc).

Moduł strdeque (pliki strdeque.h i strdeque.cc) powinien udostępniać
następujące funkcje:

unsigned long strdeque_new();

    Tworzy nową, pustą kolejkę dwustronną ciągów znaków i zwraca jej
    identyfikator.

void strdeque_delete(unsigned long id);

    Jeżeli istnieje kolejka dwustronna o identyfikatorze id, usuwa ją,
    a w przeciwnym przypadku nic nie robi.

size_t strdeque_size(unsigned long id);

    Jeżeli istnieje kolejka dwustronna o identyfikatorze id, zwraca liczbę jej
    elementów, a w przeciwnym przypadku zwraca 0.

void strdeque_insert_at(unsigned long id, size_t pos, const char* value);

    Jeżeli istnieje kolejka dwustronna o identyfikatorze id oraz value != NULL,
    wstawia element value przed pozycją pos lub na koniec kolejki, jeżeli pos
    wykracza poza kolejkę.
    Gwarancje odnośnie kosztów wstawienia na początku, na końcu i w środku
    mają być takie same jak w przypadku kontenera deque (plus koszt
    odnalezienia kolejki o danym identyfikatorze).
    Jeżeli kolejka dwustronna nie istnieje lub value == NULL, to nic nie robi.
    Pozycje w kolejce numerowane są od zera.

void strdeque_remove_at(unsigned long id, size_t pos);

    Jeżeli istnieje kolejka dwustronna o identyfikatorze id i pos nie wykracza
    poza nią, usuwa element na pozycji pos, a w przeciwnym przypadku nic nie
    robi.

const char* strdeque_get_at(unsigned long id, size_t pos);

    Jeżeli istnieje kolejka dwustronna o identyfikatorze id i pos nie wykracza
    poza kolejkę, zwraca wskaźnik do elementu na pozycji pos, a w przeciwnym
    przypadku zwraca NULL.

void strdeque_clear(unsigned long id);

    Jeżeli istnieje kolejka dwustronna o identyfikatorze id, usuwa wszystkie
    jej elementy, a w przeciwnym przypadki nic nie robi.

int strdeque_comp(unsigned long id1, unsigned long id2);

    Porównuje leksykograficznie kolejki dwustronne o identyfikatorach
    id1 i id2, zwracając
     -1, gdy kolejka(id1) < kolejka(id2),
      0, gdy kolejka(id1) = kolejka(id2),
      1, gdy kolejka(id1) > kolejka(id2).
    Jeżeli kolejka dwustronna o którymś z identyfikatorów nie istnieje, to jest
    traktowana jako leksykograficznie równa liście pustej.

Moduł strdequeconst (pliki strdequeconst.h i strdequeconst.cc) powinien
udostępniać funkcję:

unsigned long emptystrdeque();

    Zwraca identyfikator pustej kolejki dwustronnej, do której nic nie można
    wstawiać i z której nic nie można usuwać.

Moduły strdeque i strdequeconst powinny sprawdzać poprawność parametrów
i wykonania funkcji za pomocą asercji i wypisywać na standardowy strumień
błędów informacje diagnostyczne. Kompilowanie z parametrem -DNDEBUG powinno
wyłączać sprawdzanie i wypisywanie.

Przykład użycia znajduje się w pliku strdeque_test1.c. Przykład informacji
wypisywanych przez strdeque_test1 znajduje się w pliku strdeque_test1.err.
Aby umożliwić używanie modułów strdeque oraz strdequeconst w języku C++,
przygotuj pliki nagłówkowe cstrdeque oraz cstrdequeconst, które umieszczają
interfejsy modułów, odpowiednio, strdeque i strdequeconst w przestrzeni nazw
jnp1. Przykład użycia znajduje się w plikach strdeque_test2a.cc
i strdeque_test2b.cc.

Kompilowanie przykładów:

g++ -c -Wall -O2 -std=c++14 strdeque.cc -o strdeque.o
g++ -c -Wall -O2 -std=c++14 strdequeconst.cc -o strdequeconst.o
gcc -c -Wall -O2 strdeque_test1.c -o strdeque_test1.o
g++ -c -Wall -O2 -std=c++14 strdeque_test2a.cc -o strdeque_test2a.o
g++ -c -Wall -O2 -std=c++14 strdeque_test2b.cc -o strdeque_test2b.o
g++ strdeque_test1.o strdeque.o strdequeconst.o -o strdeque_test1
g++ strdeque_test2a.o strdeque.o strdequeconst.o -o strdeque_test2a
g++ strdeque_test2b.o strdeque.o strdequeconst.o -o strdeque_test2b

Oczekiwane rozwiązanie powinno korzystać z kontenerów i metod udostępnianych
przez standardową bibliotekę C++. Nie należy definiować własnych struktur lub
klas. Do implementacji kolejek należy użyć standardowego typu
std::deque<std::string>. W szczególności nie należy przechowywać przekazanych
przez użytkownika wskaźników const char* bezpośrednio, bowiem użytkownik może
po wykonaniu operacji modyfikować dane pod uprzednio przekazanym wskaźnikiem
lub zwolnić pamięć. Na przykład poniższy kod nie powinien przerwać się z powodu
niespełnionej asercji:

    unsigned long deq;
    char buf[4] = "foo";
    deq = strdeque_new();
    strdeque_insert_at(deq, 0, buf);
    buf[0] = 'b';
    assert(strdeque_get_at(deq, 0) != NULL);
    assert(strncmp(strdeque_get_at(deq, 0), "foo", 4) == 0);
    assert(strncmp(strdeque_get_at(deq, 0), "boo", 4) != 0);

Należy ukryć przed światem zewnętrznym wszystkie zmienne globalne i funkcje
pomocnicze nienależące do wyspecyfikowanego interfejsu modułu.
W rozwiązaniu nie należy nadużywać kompilacji warunkowej. Fragmenty tekstu
źródłowego realizujące wyspecyfikowane operacje na kolejkach nie powinny
zależeć od sposobu kompilacji – parametr -DNDEBUG lub jego brak (inaczej
posiadanie wersji diagnostycznej nie miałoby sensu).

Uwaga! W rozwiązaniu zadania obsługa standardowego wyjścia błędów powinna być
realizowana z użyciem strumieni C++ (tzn. biblioteki iostream).

Rozwiązanie powinno zawierać pliki strdeque.h, strdeque.cc, strdequeconst.h,
strdequeconst.cc, cstrdeque, cstrdequeconst. Pliki te należy umieścić
w repozytorium w katalogu

grupaN/zadanie2/ab123456+cd123456

lub

grupaN/zadanie2/ab123456+cd123456+ef123456

gdzie N jest numerem grupy, a ab123456, cd123456, ef123456 są identyfikatorami
członków zespołu umieszczającego to rozwiązanie.
Katalog z rozwiązaniem nie powinien zawierać innych plików, ale może zawierać
podkatalog private, gdzie można umieszczać różne pliki, np. swoje testy. Pliki
umieszczone w tym podkatalogu nie będą oceniane.
