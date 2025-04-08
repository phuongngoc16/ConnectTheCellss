#ifndef TEXT_H
#define TEXT_H

#include "graphics.h"

struct Graphics;

TTF_Font* loadFont(const char* path, int size);
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color textColor);
void showText(Graphics& graphics, const std::string& text, int x, int y, SDL_Texture* background, int fontSize = 60, SDL_Color color = {100, 100, 200, 150});

#endif

