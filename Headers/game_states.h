#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "declare.h"    
#include "graphic.h"

void countdown();

void chooselevel();

void blockInputFor(int milliseconds);

void beforeGameStarted();

void ayready();

void GameOverFor1PlayerMode(int level);

void GameOverFor2PlayerMode(int winner);

#endif 
