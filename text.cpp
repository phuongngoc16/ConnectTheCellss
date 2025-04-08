#include "text.h"


TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* gFont = TTF_OpenFont(path, size);
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}

SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color textColor) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface(textSurface);
    return texture;
}

void showText(Graphics& graphics, const std::string& text, int x, int y, SDL_Texture* background, int fontSize, SDL_Color color) {
    graphics.prepareScene(background);
    SDL_RenderPresent(graphics.renderer);

    TTF_Font* font = loadFont("C:/Windows/Fonts/BAUHS93.ttf", fontSize);
    if (!font) {
        SDL_Log("Error loading font");
        return;
    }

    SDL_Texture* textTexture = renderText(graphics.renderer, text.c_str(), font, color);
    if (!textTexture) {
        TTF_CloseFont(font);
        return;
    }
    graphics.renderTexture(textTexture, x, y);
    graphics.presentScene();

    waitUntilKeyPressed();

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

