#include "EnemyManager.h"
#include <random>

void EnemyManager::SpawnHelicopter()
{
	int direction = GetRandomValue(0, 1);
	Helicopter newHelicopter{};
	newHelicopter.PrepareHelicopter(yStartPositions[direction], static_cast<bool>(direction));
	helicopters.push_back(newHelicopter);
}

void EnemyManager::DrawHelicopters() {

	std::list<Helicopter>::iterator it;
	for (it = helicopters.begin(); it != helicopters.end(); it++) {
		it->DrawHelicopter();
	}
}

void EnemyManager::UpdateHelicopters()
{
	std::list<Helicopter>::iterator it;
	for (it = helicopters.begin(); it != helicopters.end(); it++) {
		it->UpdateHelicopter();
	}
}

void EnemyManager::ClearHelicopters()
{
	std::list<Helicopter>::iterator it;
	for (it = helicopters.begin(); it != helicopters.end(); it++) {
		it->ClearHelicopter();
	}
	helicopters.clear();
}

void EnemyManager::ClearOutOfScreenHelicopters()
{
	std::list<Helicopter>::iterator it;
	for (it = helicopters.begin(); it != helicopters.end(); it++) {
		if (it->IsOutOfScreen()) {
			it->ClearHelicopter();			
			it = helicopters.erase(it);
		}
	}
}

void EnemyManager::SpawnSoldier()
{
	Soldier soldier = {};
	int selector = GetRandomValue(0, helicopters.size() - 1);
	if (helicopters.size() > 0) {
		std::list<Helicopter>::iterator it = helicopters.begin();
		std::advance(it, selector);
		if ((it->GetPosition() > 0 && it->GetPosition() < screenWidth - 30 && it->GetPosition() != screenWidth / 2) &&
			!(it->GetPosition() > screenWidth / 2 && it->GetPosition() < screenWidth / 2 + 150  )) {
			soldier.PrepareSoldier(it->GetPosition(), 125);
			soldiers.push_back(soldier);
		}		
	}	
}

void EnemyManager::UpdateSoldiers()
{
	std::list<Soldier>::iterator it;
	for (it = soldiers.begin(); it != soldiers.end(); it++) {
		it->UpdateSoldierPosition(-1);
	}
}

void EnemyManager::DrawSoldiers()
{
	std::list<Soldier>::iterator it;
	for (it = soldiers.begin(); it != soldiers.end(); it++) {
		it->DrawSoldier();
	}
}

void EnemyManager::ClearSoldiers()
{
	std::list<Soldier>::iterator it;
	for (it = soldiers.begin(); it != soldiers.end(); it++) {
		it->ClearSoldier();
	}
	soldiers.clear();
}

int EnemyManager::GetLandedSoldiers()
{
	int landedSoldiers = 0;
	std::list<Soldier>::iterator it;
	for (it = soldiers.begin(); it != soldiers.end(); it++) {
		if (it->IsLanded()) landedSoldiers++;
	}
	return landedSoldiers;
}

void EnemyManager::ClearEnemies()
{
	ClearHelicopters();
	ClearSoldiers();
}

void EnemyManager::UpdateEnemies()
{
	UpdateHelicopters();
	UpdateSoldiers();
}

std::list<Soldier> EnemyManager::GetSoldiers()
{
	return soldiers;
}

void EnemyManager::UpdateSoldiersList(std::list<Soldier> newList)
{
	soldiers = newList;
}

std::list<Helicopter> EnemyManager::GetHelicopters()
{
	return helicopters;
}

void EnemyManager::UpdateHelicoptersList(std::list<Helicopter> newList)
{
	helicopters = newList;
}

void EnemyManager::DrawEnemies()
{
	DrawHelicopters();
	DrawSoldiers();
}
