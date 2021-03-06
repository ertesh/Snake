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

static void draw_image(SDL_Surface *img, int dest_x, int dest_y,
        int w, int h, int src_x, int src_y)
{
    SDL_Rect dest;
    dest.x = dest_x;
    dest.y = dest_y;
    SDL_Rect src;
    src.w = w;
    src.h = h;
    src.x = src_x;
    src.y = src_y;
    SDL_BlitSurface(img, &src, screen, &dest);
}

static void draw_background() {
    Image p = images[0];
    if (p.img == NULL) {
        printf("Brak tła\n");
        return;
    }
    draw_image(p.img, 0, 0);
    SDL_Flip(screen);
}

Uint32 timer_callback(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);
    return interval;
}

// Public interface
void przygotuj(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
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

void rysuj_obrazek(int numer, int x, int y)
{
    Image p = images[numer];
    if (p.img == NULL) {
        printf("Brak obrazka o numerze %d\n", numer);
        return;
    }
    draw_image(p.img, x, y);
    SDL_Flip(screen);
}

void rysuj_tlo(int x, int y, int src_x, int src_y, int szer, int wys) {
    Image p = images[0];
    if (p.img == NULL) {
        printf("Brak obrazka o numerze %d\n", 0);
        return;
    }
    draw_image(p.img, x, y, szer, wys, src_x, src_y);
    SDL_Flip(screen);
}

void graj(int interval)
{
    draw_background();
    bool done;
    SDL_AddTimer(interval, timer_callback, NULL);
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
            if(event.type == SDL_USEREVENT)
            {
                if(event.user.code == 0)
                    if (events[ZMIEN] != NULL) {
                        int ret = (int) events[ZMIEN]();
                        if (ret != 0) done = true;
                    }
            }
            Uint8* keys = SDL_GetKeyState(NULL);
            if (keys[SDLK_UP] && events[GORA] != NULL) events[GORA]();
            if (keys[SDLK_DOWN] && events[DOL] != NULL) events[DOL]();
            if (keys[SDLK_LEFT] && events[LEWO] != NULL) events[LEWO]();
            if (keys[SDLK_RIGHT] && events[PRAWO] != NULL) events[PRAWO]();
        }
        if (events[RYSUJ] != NULL) events[RYSUJ]();
    }
}

} // namespace

