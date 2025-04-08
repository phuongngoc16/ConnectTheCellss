#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "defs.h"
#include "graphics.h"
#include "Time.h"
#include "logic.h"
#include "text.h"
#include "music.h"
using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    SDL_Texture* background = nullptr;
    TTF_Font* font = nullptr;
    Mix_Music* gMusic = nullptr;
    Time timer(graphics.renderer, font, TIME_LIMIT);
    initGame(graphics, background, font, timer, gMusic);

    vector<pair<int, int>> path;
    int board[ROW][COL] = {0};
    int x, y, x1, y1;
    prepare(x, y, x1, y1, board, path);
    bool quit = false, isPlaying = true;
    SDL_Event e;
 while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                quit = true;
            }
            else if(isPlaying){
                work (x, y, x1, y1, board, e, path, quit, timer, graphics, background, isPlaying);
            }
            else if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                case SDLK_1:
                    resetGame(x, y, x1, y1, board, path, timer, isPlaying);
                    break;
                case SDLK_0:
                    quit = true;     break;
                }
            }
        }
            if (isPlaying) {
            graphics.prepareScene(background);
            timer.render();
            SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
            graphics.drawBoard(graphics.renderer, board);
            SDL_RenderPresent(graphics.renderer);
            }
    }
    SDL_DestroyTexture(background);
      graphics.quit();
    return 0;
}



