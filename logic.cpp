#include "logic.h"
#include <SDL.h>
#include "graphics.h"
#include "Time.h"
#include <algorithm>
#include "text.h"
#include "music.h"
void initGame(Graphics& graphics, SDL_Texture*& background, TTF_Font*& font, Time& timer, Mix_Music*& gMusic) {
    graphics.init();
    gMusic = loadMusic(MUSIC);
    play(gMusic);
    load_bg(graphics, BACKGROUND_1);
    font = loadFont("C:/Windows/Fonts/Arial.ttf", 35);
    timer = Time(graphics.renderer, font, TIME_LIMIT);
    timer.start();
    background = graphics.loadTexture(BACKGROUND);
    SDL_RenderCopy(graphics.renderer, background, NULL, NULL);
}

void prepare(int& x, int& y, int& x1, int& y1, int board[ROW][COL], vector<pair<int, int>>& path) {
    do {
        y1 = rand() % ROW;
        x1 = rand() % COL;
    } while (x1 == 0 && y1 == 0);
    x = 0;
    y = 0;
    board[y1][x1] = 2;
    board[y][x] = 3;
    path.push_back({x, y});
}

bool Filled(int board[ROW][COL]) {
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            if (board[i][j] == 0) return false;
    return true;
}

void work(int& x, int& y, int& x1, int& y1, int board[ROW][COL], SDL_Event& e, vector<pair<int, int>>& path, bool& quit, Time& timer, Graphics& graphics, SDL_Texture* background, bool &isPlaying) {
    srand(time(0));
    if (e.type != SDL_KEYDOWN) return;

    int newX = x, newY = y;
    switch (e.key.keysym.sym) {
        case SDLK_UP:    newY--; break;
        case SDLK_DOWN:  newY++; break;
        case SDLK_LEFT:  newX--; break;
        case SDLK_RIGHT: newX++; break;
        default: return;
    }

    if (newX >= 0 && newX < COL && newY >= 0 && newY < ROW) {
        if (board[newY][newX] == 1) {
            auto it = find(path.begin(), path.end(), make_pair(newX, newY));
            if (it != path.end()) {
                for (auto i = it + 1; i != path.end(); i++) {
                    int tx = i->first;
                    int ty = i->second;
                    if (!(tx == 0 && ty == 0) && !(tx == x1 && ty == y1))
                        board[ty][tx] = 0;
                }
                path.erase(it + 1, path.end());
                x = newX;
                y = newY;
            }
        }
        else if (board[newY][newX] == 0 || board[newY][newX] == 2 || board[newY][newX] == 3) {
            x = newX;
            y = newY;
            if (!(x == 0 && y == 0) && !(x == x1 && y == y1))
                board[y][x] = 1;
            path.push_back({x, y});
        }

        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
                board[i][j] = 0;

        for (auto& t : path) {
            int tx = t.first;
            int ty = t.second;
            board[ty][tx] = 1;
        }
        board[0][0] = 3;
        board[y1][x1] = 2;

        if (x == x1 && y == y1 && !Filled(board)) {
            for (int i = 0; i < ROW; ++i)
                for (int j = 0; j < COL; ++j)
                    if (board[i][j] == 1) board[i][j] = 0;
            x = 0;
            y = 0;
            path.clear();
            path.push_back({x, y});
            board[y][x] = 3;
            board[y1][x1] = 2;
        }

         if (timer.getTimeLeft() <= 0) {
            SDL_Texture* background2 = graphics.loadTexture(BACKGROUND_2);
            graphics.prepareScene(background2);
            showText(graphics,"GAME OVER!", 220, 150, background2);
            SDL_RenderPresent(graphics.renderer);
            SDL_Delay(2000);
            SDL_DestroyTexture(background2);
            isPlaying = false;
        }
        else if (x == x1 && y == y1 && Filled(board)) {
            int score = timer.getTimeLeft() * 10;
            SDL_Texture* background2 = graphics.loadTexture(BACKGROUND_2);
            graphics.prepareScene(background2);
            string winText = "WIN - Score: " + to_string(score);
            showText(graphics, winText, 190, 150, background2);
            SDL_DestroyTexture(background2);
            isPlaying = false;
        }
    }
}

void resetGame(int& x, int& y, int& x1, int& y1, int board[ROW][COL], vector<pair<int, int>>& path, Time& timer, bool& isPlaying) {
    x = 0;
    y = 0;
    path.clear();
    path.push_back({x, y});

    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            board[i][j] = 0;

    board[y][x] = 3;
    do {
        x1 = rand() % COL;
        y1 = rand() % ROW;
    } while (x1 == 0 && y1 == 0);

     board[y1][x1] = 2;
    timer.reset();
    isPlaying = true;
}

