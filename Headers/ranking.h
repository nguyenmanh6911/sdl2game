#ifndef RANKING_H
#define RANKING_H

#include "declare.h"

int get_highest_score(int level);

void saveScore(const string& playerName1, int score,int level);

void saveTop5Scores(int level);  

bool compareScores(const PlayerScore& a, const PlayerScore& b);

void show_ranking(int level);

#endif