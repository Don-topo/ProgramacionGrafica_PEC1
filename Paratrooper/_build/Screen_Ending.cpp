#include "Screen_Ending.h"

void Screen_Ending::InitEndingScreen(void) {
	finishScreen = 0;
	music = LoadMusicStream("resources/Lose.wav");
	music.looping = false;
	SetMusicVolume(music, 1.f);
	PlayMusicStream(music);	
}

void Screen_Ending::UpdateEndingScreen(void) {
	if (IsKeyDown(KEY_O)) finishScreen = 1;
	if (IsKeyDown(KEY_ENTER)) finishScreen = 2;
	UpdateMusicStream(music);
}

void Screen_Ending::DrawEndingScreen(void) {
	DrawText(loseTitleText, screenWidth / 2 - 75, screenHeight / 2 - 50, 24, WHITE);
	DrawText(loseMainTitleText, screenWidth / 2 - 160, screenHeight / 2 + 150, 24, WHITE);
	DrawText(loseOptionsText, screenWidth / 2 - 125, screenHeight / 2 + 200, 24, WHITE);
}

void Screen_Ending::UnloadEndingScreen(void) {
	UnloadMusicStream(music);
	finishScreen = 0;
}

int Screen_Ending::FinishEndingScreen(void) {
	return finishScreen;
}