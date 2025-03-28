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
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (soundimage) SDL_DestroyTexture(soundimage);
    if (muteimage) SDL_DestroyTexture(muteimage);
    if (highestscoreTexture) SDL_DestroyTexture(highestscoreTexture);

    if (font) TTF_CloseFont(font);
    if (font1) TTF_CloseFont(font1);

    if (music) Mix_FreeMusic(music);

    if (effect1) Mix_FreeChunk(effect1);
    if (effect2) Mix_FreeChunk(effect2);
    if (effect3) Mix_FreeChunk(effect3);

    quitSDL();
}
