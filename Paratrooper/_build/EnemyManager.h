#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "raylib.h"
#include "Helicopter.h"
#include "Soldier.h"
#include <list>
#include "GlobalGameDefines.h"


class EnemyManager
{
public:
	void DrawHelicopters();
	void SpawnHelicopter();
	void UpdateHelicopters();
	void ClearHelicopters();
	void ClearOutOfScreenHelicopters();
	void SpawnSoldier();
	void UpdateSoldiers();
	void DrawSoldiers();
	void ClearSoldiers();
	int GetLandedSoldiers();
	void DrawEnemies();
	void ClearEnemies();
	void UpdateEnemies();
	std::list<Soldier> GetSoldiers();
	void UpdateSoldiersList(std::list<Soldier> newList);
	std::list<Helicopter> GetHelicopters();
	void UpdateHelicoptersList(std::list<Helicopter> newList);
private:
	const int yStartPositions[2] = {25, 75};
	std::list<Helicopter> helicopters = {};
	std::list<Soldier> soldiers = {};
};


#endif // !ENEMY_MANAGER_H