#include "declare.h"
#include "Init.h"
#include "destroy.h"
#include "graphic.h"
#include "game_states.h"    
#include "game.h"   
#include "logic.h"  


void destroy () {
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (birdTexture) SDL_DestroyTexture(birdTexture);
    if (birdTexture1) SDL_DestroyTexture(birdTexture1);
    if (birdTexture2) SDL_DestroyTexture(birdTexture2); 
    if (pipeTexture) SDL_DestroyTexture(pipeTexture);
    if (backgroundTexture1) SDL_DestroyTexture(backgroundTexture1);
    if (backgroundTexture2) SDL_DestroyTexture(backgroundTexture2);
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (soundimage) SDL_DestroyTexture(soundimage);
    if (muteimage) SDL_DestroyTexture(muteimage);
    if (rankimage) SDL_DestroyTexture(rankimage);
    if (healthTexture) SDL_DestroyTexture(healthTexture);
    if (bombTexture) SDL_DestroyTexture(bombTexture);
    if (homeimage) SDL_DestroyTexture(homeimage);
    if (returnimage) SDL_DestroyTexture(returnimage);
    if (heart1) SDL_DestroyTexture(heart1);
    if (heart2) SDL_DestroyTexture(heart2);
    if (heart3) SDL_DestroyTexture(heart3);
    if (highestscoreTexture) SDL_DestroyTexture(highestscoreTexture);

    if (font) TTF_CloseFont(font);
    if (font1) TTF_CloseFont(font1);

    if (music) Mix_FreeMusic(music);
    if (soundflap) Mix_FreeChunk(soundflap);
    if (soundvacham) Mix_FreeChunk(soundvacham);
    if (soundting_ting) Mix_FreeChunk(soundting_ting);
    if (explode) Mix_FreeChunk(explode);

    quitSDL();
}
