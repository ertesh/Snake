#include <cstdio>
#include "guilib.h"

using namespace guilib;

void* rysuj() {
    printf("Rysuj");
    return 0;
}

void* gora() {
    printf("Gora\n");
    return 0;
}

int main() {
    przygotuj(640, 480);
    wczytaj_obrazek(0, (char*)"bg.bmp", 640, 480);
    wczytaj_obrazek(1, (char*)"img.bmp", 100, 100);
    ustaw_zdarzenie(RYSUJ, rysuj);
    ustaw_zdarzenie(GORA, gora);
    graj();
}

