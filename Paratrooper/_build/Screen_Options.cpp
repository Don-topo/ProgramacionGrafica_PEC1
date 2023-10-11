#include "Screen_Options.h"

void Screen_Options::InitOptionsScreen(void) {
	finishScreen = 0;
}

void Screen_Options::UpdateOptionsScreen(void) {
	if(IsKeyDown(KEY_O)) finishScreen = 1;
}

void Screen_Options::DrawOptionsScreen(void) {
	DrawText(optionsExplainText, screenWidth / 4 - sizeof(optionsExplainText) * 10, screenHeight / 4, 24, WHITE);
	DrawText(optionsShootText, screenWidth / 2 - 150, screenHeight / 2, 24, WHITE);
	DrawText(optionsMovementText, screenWidth / 4 - 100, screenHeight / 2 + 50, 24, WHITE);
	DrawText(optionsReturnText, screenWidth / 2 - 175, screenHeight - 250, 24 , WHITE);
}

void Screen_Options::UnloadOptionsScreen(void) {
	finishScreen = 0;
}

int Screen_Options::FinishOptionsScreen(void) {
	return finishScreen;
}