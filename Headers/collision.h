#ifndef COLLISION_H
#define COLLISION_H

#include "declare.h"
#include "Init.h"
#include "game_states.h"
#include "reset.h"

bool checkvacham(SDL_Rect a, SDL_Rect b);

void xulivacham_screen ();

void xulivacham_screen_mode2();

void xuliPipe(int toc_do);

void xuliPipe_mode2(int toc_do);

void xuliBomb(int toc_do);

void xuliHealth(int toc_do);






#endif