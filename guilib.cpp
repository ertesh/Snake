#include <SDL/SDL.h>
#include <map>
#include "guilib.h"
using std::map;

namespace guilib {

struct Image {
    SDL_Surface* img;
    int width;
    int height;
};

static SDL_Surface* screen;
static map<int, Image> images;
static map<Zdarzenie, Funkcja> events;

static void draw_image(SDL_Surface *img, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(img, NULL, screen, &dest);
}

static void draw_image(SDL_Surface *img, int x, int y,
                                        int w, int h, int x2, int y2)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_Rect dest2;
    dest2.x = x2;
    dest2.y = y2;
    dest2.w = w;
    dest2.h = h;
    SDL_BlitSurface(img, &dest2, screen, &dest);
}

void draw_background() {
    Image p = images[0];
    if (p.img == NULL) {
        printf("Brak tła\n");
        return;
    }
    draw_image(p.img, 0, 0);
    SDL_Flip(screen);
}

void draw(Funkcja f)
{
    return;
}
// Public interface

void przygotuj(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(width, height, 32,
        SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Unable to set video: %s\n", SDL_GetError());
        exit(1);
    }
}

bool wczytaj_obrazek(int numer, char* nazwa, int x, int y)
{
    Image p;
    p.width = x;
    p.height = y;
    p.img = SDL_LoadBMP(nazwa);
    if (p.img == NULL) {
        printf("Image %s not loaded.\n", nazwa);
        return false;
    }
    images[numer] = p;
    return true;
}

void ustaw_zdarzenie(Zdarzenie z, Funkcja f)
{
    events[z] = f;
}

void graj()
{
    draw_background();
    bool done;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done = true;
                }
            }
            Uint8* keys = SDL_GetKeyState(NULL);
            if (keys[SDLK_UP]) events[GORA];
            if (keys[SDLK_DOWN]) events[DOL];
            if (keys[SDLK_LEFT]) events[LEWO];
            if (keys[SDLK_RIGHT]) events[PRAWO];
            draw(events[RYSUJ]);
        }
    }
}

} // namespace

