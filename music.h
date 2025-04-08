#ifndef MUSIC_H
#define MUSIC_H

#include "graphics.h"
    Mix_Music *loadMusic(const char* path);
    void play(Mix_Music *gMusic);
#endif
