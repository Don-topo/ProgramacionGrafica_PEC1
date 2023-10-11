#include "TextureManager.h"

void TextureManager::PrepareGameplayTextures()
{
	// Enemies
	soldierTexture = LoadTexture("resources/Soldier.png");
	deadTexture = LoadTexture("resources/Dead.png");
	helicopterLeftTexture = LoadTexture("resources/Helicopter_Left.png");
	helicopterRightTexture = LoadTexture("resources/Helicopter_Right.png");
	// Player
	playerBaseTexture = LoadTexture("resources/PlayerBody.png");
	playerCannonTexture = LoadTexture("resources/Turret.png");
}

Texture2D TextureManager::GetSoldierTexture()
{
	return soldierTexture;
}

Texture2D TextureManager::GetHelicopterLeftTexture()
{
	return helicopterLeftTexture;
}

Texture2D TextureManager::GetHelicopterRightTexture()
{
	return helicopterRightTexture;
}

Texture2D TextureManager::GetDeadTexture()
{
	return deadTexture;
}

Texture2D TextureManager::GetPlayerBaseTexture()
{
	return playerBaseTexture;
}

Texture2D TextureManager::GetPlayerCannonTexture()
{
	return playerCannonTexture;
}

void TextureManager::UnloadGameplayTextures()
{
	// Unload enemies
	UnloadTexture(soldierTexture);
	UnloadTexture(deadTexture);
	UnloadTexture(helicopterLeftTexture);
	UnloadTexture(helicopterRightTexture);
	// Unload player
	UnloadTexture(playerBaseTexture);
	UnloadTexture(playerCannonTexture);
}
