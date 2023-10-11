#ifndef SCREEN_TITLE_H
#define SCREEN_TITLE_H


#include "raylib.h"
#include "GlobalGameDefines.h"


struct title
{
	Texture2D titleTexture;
	int xPos;
	int yPos;
};
class Screen_Title
{

public:
	void InitTitleScreen(void);
	void UpdateTitleScreen(void);
	void DrawTitleScreen(void);
	void UnloadTitleScreen(void);
	int FinishTitleScreen(void);
private:
	const char* titleAutorText = "   by\nRuben G.";
	const char* titlePlayText = "Press Enter for Playing";
	const char* titleOptionsText = "Press 'O' for Instructions";
	title titleInfo;
	int finishScreen = 0;
	Music music;
};

#endif
