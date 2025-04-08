#include <SDL.h>
#include<iostream>
#include <SDL_image.h>
#include "graphics.h"
#include <SDL_ttf.h>

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

     if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
        Mix_GetError() );
}
  }

void Graphics::prepareScene(SDL_Texture * background)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}


void Graphics::quit()
{
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::drawBoard(SDL_Renderer* renderer, int board[ROW][COL])
{
     for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            SDL_Rect cell;
            cell.x = j * CELL_SIZE + 240;
            cell.y = i * CELL_SIZE + 150;
            cell.w = CELL_SIZE;
            cell.h = CELL_SIZE;

            if(board[i][j] == 2)
                SDL_SetRenderDrawColor(renderer, 253, 253, 150, 255);// vang: kết thúc
            else if(board[i][j] == 3)
                SDL_SetRenderDrawColor(renderer, 119, 221, 119, 255 ); // xanh la: bắt đầu
            else
            if (board[i][j] == 0)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // trắng: chưa đi
            else
                SDL_SetRenderDrawColor(renderer, 174, 198, 207, 10); // xanh duong

            SDL_RenderFillRect(renderer, &cell); // ve hcn day mau
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cell); //đường viền
        }
    }
}
void load_bg(Graphics& graphics, const char* background) {
    SDL_Texture* bg = graphics.loadTexture(background);
    graphics.prepareScene(bg);
    SDL_RenderPresent(graphics.renderer);
    waitUntilKeyPressed();
    SDL_DestroyTexture(bg);
}
