#include "guilib.h"

using namespace guilib;

int main() {
    przygotuj(640, 480);
    wczytaj_obrazek(0, (char*)"bg.bmp", 640, 480);
    wczytaj_obrazek(1, (char*)"img.bmp", 100, 100);
    graj();
}

