#ifndef GLOBAL_GAME_DEFINES_H
#define GLOBAL_GAME_DEFINES_H

#include <iostream>

const static int screenWidth = 800;
const static int screenHeight = 800;
const static char* screenTitleText = "Paratrooper";
const static int framesPerSecond = 60;
typedef enum GameScreen { LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

extern GameScreen currentScreen;

#endif