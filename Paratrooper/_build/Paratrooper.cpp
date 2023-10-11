#include "raylib.h"
#include "GlobalGameDefines.h"

#include "Screen_Logo.h"
#include "Screen_Title.h"
#include "Screen_Options.h"
#include "Screen_Ending.h"
#include "Screen_Gameplay.h"

GameScreen currentScreen = static_cast<GameScreen>(0);
Screen_Logo screenLogo;
Screen_Title screenTitle;
Screen_Options screenOptions;
Screen_Gameplay screenGameplay;
Screen_Ending screenEnding;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;

static void UpdateDrawFrame(void);          // Update and draw one frame

int main() {

	InitWindow(screenWidth, screenHeight, screenTitleText);
	SetTargetFPS(framesPerSecond);
    InitAudioDevice();

	currentScreen = static_cast<GameScreen>(0);
	screenLogo.InitLogoScreen();

	while (!WindowShouldClose()) {
		UpdateDrawFrame();
	}

	switch (currentScreen)
	{
		case LOGO: screenLogo.UnloadLogoScreen(); break;
		case TITLE: screenTitle.UnloadTitleScreen(); break;
        case OPTIONS: screenOptions.UnloadOptionsScreen(); break;
		case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
		case ENDING: screenEnding.UnloadEndingScreen(); break;
		default: break;
	}
    CloseAudioDevice();
	CloseWindow();
	return 0;
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Request transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: screenLogo.UnloadLogoScreen(); break;
                case TITLE: screenTitle.UnloadTitleScreen(); break;
                case OPTIONS: screenOptions.UnloadOptionsScreen(); break;
                case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
                case ENDING: screenEnding.UnloadEndingScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: screenLogo.InitLogoScreen(); break;
                case TITLE: screenTitle.InitTitleScreen(); break;
                case GAMEPLAY: screenGameplay.InitGameplayScreen(); break;
                case ENDING: screenEnding.InitEndingScreen(); break;
                default: break;
            }

            currentScreen = static_cast<GameScreen>(transToScreen);

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    //UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        switch (currentScreen)
        {
        case LOGO:
        {
            screenLogo.UpdateLogoScreen();

            if (screenLogo.FinishLogoScreen()) TransitionToScreen(TITLE);

        } break;
        case TITLE:
        {
            screenTitle.UpdateTitleScreen();

            if (screenTitle.FinishTitleScreen() == 2) TransitionToScreen(OPTIONS);
            else if (screenTitle.FinishTitleScreen() == 3) TransitionToScreen(GAMEPLAY);

        } break;
        case OPTIONS:
        {
            screenOptions.UpdateOptionsScreen();

            if (screenOptions.FinishOptionsScreen()) TransitionToScreen(TITLE);

        } break;
        case GAMEPLAY:
        {
            screenGameplay.UpdateGameplayScreen();

            if (screenGameplay.FinishGameplayScreen() == 1) TransitionToScreen(ENDING);

        } break;
        case ENDING:
        {
            screenEnding.UpdateEndingScreen();

            if (screenEnding.FinishEndingScreen() == 1) TransitionToScreen(OPTIONS);
            else if (screenEnding.FinishEndingScreen() == 2) TransitionToScreen(GAMEPLAY);

        } break;
        default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);

    switch (currentScreen)
    {
        case LOGO: screenLogo.DrawLogoScreen(); break;
        case TITLE: screenTitle.DrawTitleScreen(); break;
        case OPTIONS: screenOptions.DrawOptionsScreen(); break;
        case GAMEPLAY: screenGameplay.DrawGameplayScreen(); break;
        case ENDING: screenEnding.DrawEndingScreen(); break;
        default: break;
    }

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();

    EndDrawing();
    //----------------------------------------------------------------------------------
}
