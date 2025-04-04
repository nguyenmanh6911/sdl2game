#include "declare.h"
#include "Init.h"
#include "graphic.h"
#include "game_states.h"
#include "reset.h"
#include "game.h"
#include "destroy.h"
#include "instruction.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
    srand(time(0));
    init();

    while (running) {
        if (gamestarted == false) beforeGameStarted();
        else if(gamestarted==true && gameover==false && gamemode==1&&level==1) Game_Level1();
        else if(gamestarted==true && gameover==false && gamemode==1&&level==2) Game_Level2();
        else if(gamestarted==true && gameover==false && gamemode==1&&level==3) Game_Level3();
        else if (gamestarted==true&&gameover==false&&gamemode==2) Mode2Player();
        else if (gamestarted==true && gameover==true&&gamemode==1) GameOverFor1PlayerMode(level);
        else if (gameover == true && gamestarted == true && gamemode == 2) GameOverFor2PlayerMode(winner);
    }

    destroy();
    return 0;
}
