#include <cstdio>
#include "guilib.h"

using namespace guilib;
int x = 50, y = 50;
void* rysuj() {
    rysuj_obrazek(1, x, y);
    return 0;
}

void* gora() {
    y -= 5;
    return 0;
}

void* dol() {
    y += 5;
    return 0;
}

void* lewo() {
    x -= 5;
    return 0;
}

void* prawo() {
    x += 5;
    return 0;
}

void* zmien() {
    return 0;
}

int main() {
    przygotuj(640, 480);
    wczytaj_obrazek(0, (char*)"bg.bmp", 640, 480);
    wczytaj_obrazek(1, (char*)"img.bmp", 128, 128);
    ustaw_zdarzenie(RYSUJ, rysuj);
    ustaw_zdarzenie(GORA, gora);
    ustaw_zdarzenie(DOL, dol);
    ustaw_zdarzenie(LEWO, lewo);
    ustaw_zdarzenie(PRAWO, prawo);
    ustaw_zdarzenie(ZMIEN, zmien);
    graj();
}

