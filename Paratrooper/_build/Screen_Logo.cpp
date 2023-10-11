#include "Screen_Logo.h"

void Screen_Logo::InitLogoScreen(void)
{	
	logoInfo.logoTexture = LoadTexture("resources/Logo.png");
	logoInfo.xPos = (screenWidth / 2) - (logoInfo.logoTexture.width / 2);
	logoInfo.yPos = (screenHeight / 2) - (logoInfo.logoTexture.height / 2);
	finishScreen = 0;
}

void Screen_Logo::UpdateLogoScreen(void)
{
	transAlpha += 0.01f;
	screenSecondsRemaining -= 1;
	if (screenSecondsRemaining <= 0) {
		finishScreen = 1;
	}	
}

void Screen_Logo::DrawLogoScreen(void)
{
	DrawTexture(logoInfo.logoTexture, logoInfo.xPos, logoInfo.yPos, Fade(WHITE, transAlpha));
}

void Screen_Logo::UnloadLogoScreen(void)
{
	UnloadTexture(logoInfo.logoTexture);
}

int Screen_Logo::FinishLogoScreen(void)
{
	return finishScreen;
}
