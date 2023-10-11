#ifndef SCREEN_OPTIONS_H
#define SCREEN_OPTIONS_H


#include "raylib.h"
#include "GlobalGameDefines.h"

class Screen_Options
{

public:
	void InitOptionsScreen(void);
	void UpdateOptionsScreen(void);
	void DrawOptionsScreen(void);
	void UnloadOptionsScreen(void);
	int FinishOptionsScreen(void);
private:
	int finishScreen;
	const char* optionsExplainText = "Do not allow enemy paratroopers to land\non either side of you gun base. If seven\nparatroopers land your base you will loose";
	const char* optionsShootText = "Press space to shoot";
	const char* optionsMovementText = "Press 'A' to move the turret counterclockwise.\n\tPress 'D' to move the turret clockwise";
	const char* optionsReturnText = "Press 'O' to return to Title";
};

#endif // !SCREEN_OPTIONS_H