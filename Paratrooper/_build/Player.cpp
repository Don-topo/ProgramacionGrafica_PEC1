#include "Player.h"

void Player::PreparePlayer()
{
	playerBase = LoadTexture("resources/PlayerBody.png");
	playerCannon = LoadTexture("resources/Turret.png");
	cannonScale = 0.8f;
	cannonOriginRectangle = { 0.f, 0.f, (float)playerCannon.width, (float)playerCannon.height };
	cannonDestRectangle = { screenWidth / 2.f,(float) screenHeight - playerBase.height + 7 , (float)playerCannon.width * cannonScale, (float)playerCannon.height * cannonScale };
	playerCannonV = { (float)playerCannon.width / 2.f, (float)playerCannon.height };
	cannonRotation = 0.f;
	// Shoot
	isShooting = false;
	shootPosition = { screenWidth / 2, (float)screenHeight - playerBase.height - (playerCannon.height) };
}

void Player::DrawPlayer()
{
	DrawTexturePro(playerCannon, cannonOriginRectangle, cannonDestRectangle, playerCannonV, cannonRotation, WHITE);
	DrawTexture(playerBase, (screenWidth / 2.f) - (playerBase.width / 2.f), screenHeight - playerBase.height, WHITE);
}

void Player::ClearPlayer()
{
	UnloadTexture(playerBase);
	UnloadTexture(playerCannon);
}

void Player::MovePlayer() {
	cannonRotation++;
}

void Player::SetCannonRotation(float newRotation)
{
	cannonRotation += newRotation;
}

float Player::GetCannonRotation()
{
	return cannonRotation;
}

Rectangle Player::GetDestination()
{
	return cannonDestRectangle;
}

Vector2 Player::GetShootPosition()
{
	Vector2 test = { screenWidth / 2, (screenHeight - playerBase.height) };
	return test;
}

Vector2 Player::GetCannonDimensions()
{
	return playerCannonV;
}

