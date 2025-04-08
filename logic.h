#ifndef LOGIC_H
#define LOGIC_H
#include "defs.h"
#include "graphics.h"
#include "time.h"
#include <vector>
using namespace std;
void initGame(Graphics& graphics, SDL_Texture*& background, TTF_Font*& font, Time& timer, Mix_Music*& gMusic);
void prepare(int& x, int& y, int& x1, int& y1, int board[ROW][COL], vector<pair<int, int>>& path);
bool Filled(int board[ROW][COL]);
void work(int& x, int& y, int& x1, int& y1, int board[ROW][COL], SDL_Event& e, vector<pair<int, int>>& path, bool& quit, Time& timer, Graphics& graphics, SDL_Texture* background, bool & isPlaying);
void resetGame(int& x, int& y, int& x1, int& y1, int board[ROW][COL], vector<pair<int, int>>& path, Time& timer, bool& isPlaying);
#endif

