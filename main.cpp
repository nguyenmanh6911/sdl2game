#include "declare.h"
#include "Init.h"
#include "graphic.h"
#include "game_states.h"
#include "logic.h"
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
        else if(gamestarted==true && gameover==false && gamemode==1&&level==1) ingame1();
        else if(gamestarted==true && gameover==false && gamemode==1&&level==2) ingame2();
        else if(gamestarted==true && gameover==false && gamemode==1&&level==3) ingame3();
        else if (gamestarted==true&&gameover==false&&gamemode==2) playmode();
        else if (gamestarted==true && gameover==true&&gamemode==1) GameOver();
        else if (gameover==true && gamestarted==true&&gamemode==2&&winner==1) GameOver1();
        else if (gameover==true && gamestarted==true&&gamemode==2&&winner==2) GameOver2();
    }

    destroy();
    return 0;
}
