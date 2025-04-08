#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <SDL_ttf.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <SDL_mixer.h>
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    void logErrorAndExit(const char* msg, const char* error);
    void init();
    void presentScene();
    void prepareScene(SDL_Texture * background);
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void drawBoard(SDL_Renderer* renderer, int board[ROW][COL]);
    void renderTimer(SDL_Renderer* renderer, TTF_Font* font, Uint32 startTime, Graphics& graphics) ;

    void quit();

};
void load_bg(Graphics& graphics, const char* background);

void waitUntilKeyPressed();
#endif

