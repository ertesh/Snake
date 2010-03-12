#ifndef _GUILIB_H_
#define _GUILIB_H_

namespace guilib {

typedef void*(*Funkcja)();

// Tą funkcję trzeba wywołać przed używaniem biblioteki.
// Jako parametry należy podać długość i szerokość okna.
void przygotuj(int x, int y);

// Wczyta do programu pod podany numer obrazek z pliku.
// Kolejne parametry to długość i szerokość obrazka.
// Obrazek wczytany pod numer 0 stanie się tłem.
// Funkcja zwraca prawdę, gdy udało się poprawnie wczytać obrazek.
// Obrazki powinny być w formacie BMP.
bool wczytaj_obrazek(int numer, char* nazwa, int x, int y);

// Zdarzenia, które możemy obsłużyć.
enum Zdarzenie {
    RYSUJ, PRAWO, LEWO, GORA, DOL
};

// Wywołujemy tą funkcję, aby przypisać jednemu z powyższych zdarzeń
// pewne zachowanie. Jako drugi parametr podajemy funkcję,
// która zostanie wywołana po wystąpieniu zdarzenia.
void ustaw_zdarzenie(Zdarzenie z, Funkcja);

// Główna pętla programu, kończy się, gdy zamkniemy okno.
void graj();

} // namespace

#endif