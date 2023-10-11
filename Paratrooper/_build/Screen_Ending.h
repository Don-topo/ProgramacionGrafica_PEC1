#ifndef SCREEN_ENDING_H
#define SCREEN_ENDING_H

#include "raylib.h"
#include "GlobalGameDefines.h"

class Screen_Ending
{
public:
	void InitEndingScreen(void);
	void UpdateEndingScreen(void);
	void DrawEndingScreen(void);
	void UnloadEndingScreen(void);
	int FinishEndingScreen(void);
private:
	const char* loseTitleText = "you LOOSE!! :(";
	const char* loseMainTitleText = "Press Enter for Playing Again";
	const char* loseOptionsText = "Press 'O' for Options";
	int finishScreen;
	Music music;
};

#endif // !SCREEN_ENDING_H