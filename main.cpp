#include <cstdio>
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
};

Snake wezyk;
Plansza plansza;

void* rysuj() {
    rysuj_obrazek(0, 0, 0);
    for (int i = 0; i < plansza.szerokosc; ++i) {
        for (int j = 0; j < plansza.wysokosc; ++j) {
            int x = plansza.rozmiar * i;
            int y = plansza.rozmiar * j;
            if (plansza.mapa[i][j] > 0)
                rysuj_obrazek(plansza.mapa[i][j], x, y);
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
    Punkt p = wezyk.q.front();
    wezyk.q.pop();
    plansza.mapa[p.x][p.y] = 0;
    p = wezyk.q.back();
    switch (wezyk.dir) {
        case UP: --p.y; break;
        case RIGHT: ++p.x; break;
        case DOWN: ++p.y; break;
        case LEFT: --p.x; break;
    }
    p.y = (p.y + plansza.wysokosc) % plansza.wysokosc;
    p.x = (p.x + plansza.szerokosc) % plansza.szerokosc;
    // TODO
    debug(printf("%d %d\n", p.x, p.y));
    plansza.mapa[p.x][p.y] = 1;
    wezyk.q.push(p);
    return 0;
}

int main() {
    wezyk.len = 3;
    wezyk.q.push(Punkt(0,0));
    wezyk.q.push(Punkt(1,0));
    wezyk.q.push(Punkt(2,0));
    wezyk.dir = RIGHT;
    plansza.rozmiar = 20;
    plansza.szerokosc = 32;
    plansza.wysokosc = 24;
    int szer_ekranu = plansza.szerokosc * plansza.rozmiar;
    int wys_ekranu = plansza.wysokosc * plansza.rozmiar;
    przygotuj(szer_ekranu, wys_ekranu);
    wczytaj_obrazek(0, (char*)"bg.bmp", 640, 480);
//    wczytaj_obrazek(1, (char*)"1.bmp", 300, 300);
//    wczytaj_obrazek(2, (char*)"2.bmp", 300, 300);
//    wczytaj_obrazek(3, (char*)"3.bmp", 300, 300);
    wczytaj_obrazek(1, (char*)"4.bmp", plansza.rozmiar, plansza.rozmiar);
    ustaw_zdarzenie(RYSUJ, rysuj);
    ustaw_zdarzenie(GORA, gora);
    ustaw_zdarzenie(DOL, dol);
    ustaw_zdarzenie(LEWO, lewo);
    ustaw_zdarzenie(PRAWO, prawo);
    ustaw_zdarzenie(ZMIEN, zmien);
    graj(50);
}

