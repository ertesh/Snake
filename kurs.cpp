#include <SDL/SDL.h>
SDL_Surface* bg;
SDL_Surface* img;
SDL_Surface* screen;

void load_images() {
    bg = SDL_LoadBMP("bg.bmp");
    if (bg == NULL) {
        printf("Background not loaded.\n");
    }
    img = SDL_LoadBMP("img.bmp");
    if (img == NULL) {
        printf("Image not loaded.\n");
    }
}

void DrawIMG(SDL_Surface *img, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(img, NULL, screen, &dest);
}

void DrawIMG(SDL_Surface *img, int x, int y,
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
    DrawIMG(bg, 0, 0);
}

void draw_scene(SDL_Surface* screen, int xpos, int ypos) {
  DrawIMG(bg, xpos-2, ypos-2, 132, 132, xpos-2, ypos-2);
  DrawIMG(img, xpos, ypos);
  SDL_Flip(screen);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(640, 480, 32,
        SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }
    load_images();
    draw_background();
    bool done = false;
    int xpos = 0;
    int ypos = 0;
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
            if (keys[SDLK_UP]) ypos -= 1;
            if (keys[SDLK_DOWN]) ypos += 1;
            if (keys[SDLK_LEFT]) xpos -= 1;
            if (keys[SDLK_RIGHT]) xpos += 1;
            draw_scene(screen, xpos, ypos);
        }
    }
   // SDL_Delay(2000);
}

