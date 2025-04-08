#include "Time.h"


using namespace std;

Time::Time(SDL_Renderer* renderer, TTF_Font* font, int timeLimit)
    : renderer(renderer), font(font), timeLimit(timeLimit), startTime(0) {}

void Time::start() {
    startTime = SDL_GetTicks();
}

int Time::getTimeLeft() const {
    Uint32 currentTime = SDL_GetTicks();
    int secondsPassed = (currentTime - startTime) / 1000;
    return max(0, timeLimit - secondsPassed);
}

void Time::render() {
    int timeLeft = getTimeLeft();
    string timeText = "TIME: " + to_string(timeLeft) + "S";

    SDL_Color color = {100, 100, 200, 150};
    SDL_Surface* surface = TTF_RenderText_Solid(font, timeText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect frame = {330, 35, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &frame);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Time::reset() {
   startTime = SDL_GetTicks();
}
