#ifndef TIME_H
#define TIME_H
#include "graphics.h"
#include <ctime>
#include <cstdlib>
class Time {
public:
    Time(SDL_Renderer* renderer, TTF_Font* font, int timeLimit);
    void start();
    void render();
    void reset();
    int getTimeLeft() const;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    Uint32 startTime;
    int timeLimit;
};

#endif

