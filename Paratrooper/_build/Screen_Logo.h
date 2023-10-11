#ifndef SCREEN_LOGO_H
#define SCREEN_LOGO_H

#include "raylib.h"
#include "GlobalGameDefines.h"

struct logo
{
	Texture2D logoTexture;
	int xPos;
	int yPos;
};

class Screen_Logo {
public:
	void InitLogoScreen(void);
	void UpdateLogoScreen(void);
	void DrawLogoScreen(void);
	void UnloadLogoScreen(void);
	int FinishLogoScreen(void);
private:
	int screenSecondsRemaining = 200;
	int finishScreen;
	logo logoInfo;
	float transAlpha = 0.0f;
};

#endif // !SCREEN_LOGO_H


