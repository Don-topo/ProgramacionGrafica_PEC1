#include "Screen_Title.h"

void Screen_Title::InitTitleScreen(void) {
	titleInfo.titleTexture = LoadTexture("resources/Title.png");
	music = LoadMusicStream("resources/intro_music.ogg");
	SetMusicVolume(music, 1.f);
	music.looping = false;
	PlayMusicStream(music);
	titleInfo.xPos = (screenWidth / 2) - (titleInfo.titleTexture.width / 2);
	titleInfo.yPos = (screenHeight / 4) - (titleInfo.titleTexture.height / 2);
	finishScreen = 0;
}

void Screen_Title::UpdateTitleScreen(void) {
	if (IsKeyDown(KEY_ENTER)) finishScreen = 3;
	if (IsKeyDown(KEY_O)) finishScreen = 2;
	UpdateMusicStream(music);
}

void Screen_Title::DrawTitleScreen(void) {
	DrawTexture(titleInfo.titleTexture, titleInfo.xPos, titleInfo.yPos, WHITE);
	DrawText(titleAutorText, screenWidth / 2 - 25, (titleInfo.yPos + titleInfo.titleTexture.height * 2), 24, WHITE);
	DrawText(titlePlayText, (screenWidth / 2 - 235), (titleInfo.yPos + titleInfo.titleTexture.height * 4), 36, WHITE);
	DrawText(titleOptionsText, (screenWidth / 2 - 250), (titleInfo.yPos + titleInfo.titleTexture.height * 5), 36, WHITE);
}

void Screen_Title::UnloadTitleScreen(void) {
	UnloadTexture(titleInfo.titleTexture);
	UnloadMusicStream(music);
	finishScreen = 0;
}

int Screen_Title::FinishTitleScreen(void) {
	return finishScreen;
}
