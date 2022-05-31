#ifndef SAVEUTILS_H
#define SAVEUTILS_H
//the save system in this game is mostly based off of how Rimworld manages saving. The only real difference is that the save and load functions are 2 different functions whereas in Rimworld, exposedata handles both

//return 0 = success. 1 = failure
int saveToXml(string saveName, playerInfo *player);

//return 0 = success. 1 = failed
int loadFromXml(string saveName, playerInfo *player, SDL_Renderer *ren);

#include "saveutils.hpp"

#endif