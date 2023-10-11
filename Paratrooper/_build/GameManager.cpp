#include "GameManager.h"

GameManager::GameManager()
{
	score = 0;
	timePlayed = 0;
	landedSoldiers = 0;	
}

void GameManager::PrepareGameManager()
{
	landedSoldiers = 0;
	score = 0;
	timePlayed = 0;	
}

bool GameManager::GameIsOver()
{
	return (landedSoldiers >= 5);
}

void GameManager::UpdateScore(int value)
{
	score += value;
}

void GameManager::UpdateLandedSoldiers(int landed)
{
	landedSoldiers = landed;
}

void GameManager::UpdateTimePlayed()
{
	timePlayed++;
}

void GameManager::Shoot()
{
	if (score > 0) score--;
}

int GameManager::GetTimePlayed()
{
	return timePlayed;
}

int GameManager::GetLandedSoldiers()
{
	return landedSoldiers;
}

int GameManager::GetScore()
{
	return score;
}
