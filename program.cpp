#include <cstdio>
#include <cstdlib>
#include <queue>
#include "guilib.h"

using namespace std;
using namespace guilib;

#define debug(a) ;
#define MAX_WIDTH 100
#define MAX_HEIGHT 100

enum Kierunek {
    UP, DOWN, LEFT, RIGHT
};

enum Pole {
    PLANSZA, WAZ, OWOC
};

struct Punkt {
    int x;
    int y;
    Punkt(): x(0), y(0) {}
    Punkt(int a, int b): x(a), y(b) {}
};

struct Snake {
    queue<Punkt> q;
    Kierunek dir;
    int len;
};

struct Plansza {
    int wysokosc;
    int szerokosc;
    int rozmiar;
    int mapa[MAX_WIDTH][MAX_HEIGHT];
    bool zmiana[MAX_WIDTH][MAX_HEIGHT];
};

struct Owoce {
    int ile_owocow;
    int limit_owocow;
};

Snake wezyk;
Plansza plansza;
Owoce owoce;
int wynik;

void dodaj_owoc() {
    while (true) {
        int x = rand() % plansza.szerokosc;
        int y = rand() % plansza.wysokosc;
        if (plansza.mapa[x][y] == PLANSZA) {
            plansza.mapa[x][y] = OWOC;
            plansza.zmiana[x][y] = true;
            owoce.ile_owocow++;
            break;
        }
    }
}

void* rysuj() {
    for (int i = 0; i < plansza.szerokosc; ++i) {
        for (int j = 0; j < plansza.wysokosc; ++j) {
            if (plansza.zmiana[i][j]) {
                int x = plansza.rozmiar * i;
                int y = plansza.rozmiar * j;
                if (plansza.mapa[i][j] == 0)
                    rysuj_tlo(x, y, x, y, plansza.rozmiar, plansza.rozmiar);
                else
                    rysuj_obrazek(plansza.mapa[i][j], x, y);
                plansza.zmiana[i][j] = 0;
            }
        }
    }
    return 0;
}

void* gora() {
    debug(printf("Gora\n"));
    if (wezyk.dir == LEFT || wezyk.dir == RIGHT)
        wezyk.dir = UP;
    return 0;
}

void* dol() {
    debug(printf("Dol\n"));
    if (wezyk.dir == LEFT || wezyk.dir == RIGHT)
        wezyk.dir = DOWN;
    return 0;
}

void* lewo() {
    debug(printf("Lewo\n"));
    if (wezyk.dir == UP || wezyk.dir == DOWN)
        wezyk.dir = LEFT;
    return 0;
}

void* prawo() {
    debug(printf("Prawo\n"));
    if (wezyk.dir == UP || wezyk.dir == DOWN)
        wezyk.dir = RIGHT;
    return 0;
}

void* zmien() {
    debug(printf("Zmien\n"));
    // Przesuń głowę węża
    Punkt p = wezyk.q.back();
    switch (wezyk.dir) {
        case UP: --p.y; break;
        case RIGHT: ++p.x; break;
        case DOWN: ++p.y; break;
        case LEFT: --p.x; break;
    }
    p.x = (p.x + plansza.szerokosc) % plansza.szerokosc;
    p.y = (p.y + plansza.wysokosc) % plansza.wysokosc;
    switch(plansza.mapa[p.x][p.y]) {
        case PLANSZA:
            plansza.mapa[p.x][p.y] = WAZ;
            plansza.zmiana[p.x][p.y] = 1;
            wezyk.q.push(p);
            // Usuń ogon węża
            p = wezyk.q.front();
            wezyk.q.pop();
            plansza.mapa[p.x][p.y] = PLANSZA;
            plansza.zmiana[p.x][p.y] = 1;
            break;
        case OWOC:
            plansza.mapa[p.x][p.y] = WAZ;
            plansza.zmiana[p.x][p.y] = 1;
            wezyk.q.push(p);
            ++wezyk.len;
            wynik += 10;
            printf("%d\n", wynik);
            --owoce.ile_owocow;
            if (owoce.ile_owocow < owoce.limit_owocow) {
                dodaj_owoc();
            }
            break;
        case WAZ:
            // Kolizja, koniec gry
            printf("Koniec gry\n");
            printf("Wynik = %d\n", wynik);
            return (void*) 1;
    }
    return 0;
}

int main() {
    wynik = 0;
    wezyk.len = 3;
    wezyk.q.push(Punkt(0,0));
    wezyk.q.push(Punkt(1,0));
    wezyk.q.push(Punkt(2,0));
    wezyk.dir = RIGHT;
    plansza.rozmiar = 20;
    plansza.szerokosc = 32;
    plansza.wysokosc = 24;
    owoce.ile_owocow = 0;
    owoce.limit_owocow = 3;
    for (int i = 0; i < 3; ++i) dodaj_owoc();

    int szer_ekranu = plansza.szerokosc * plansza.rozmiar;
    int wys_ekranu = plansza.wysokosc * plansza.rozmiar;
    przygotuj(szer_ekranu, wys_ekranu);
    wczytaj_obrazek(0, (char*)"bg.bmp", 640, 480);
    wczytaj_obrazek(1, (char*)"snake.bmp", plansza.rozmiar, plansza.rozmiar);
    wczytaj_obrazek(2, (char*)"apple.bmp", plansza.rozmiar, plansza.rozmiar);
    ustaw_zdarzenie(RYSUJ, rysuj);
    ustaw_zdarzenie(GORA, gora);
    ustaw_zdarzenie(DOL, dol);
    ustaw_zdarzenie(LEWO, lewo);
    ustaw_zdarzenie(PRAWO, prawo);
    ustaw_zdarzenie(ZMIEN, zmien);
    graj(100);
}

