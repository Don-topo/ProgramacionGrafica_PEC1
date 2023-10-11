#ifndef SOLDIER_H
#define SOLDIER_H

#include "raylib.h"
#include "GlobalGameDefines.h"
#include "TextureManager.h"

class Soldier
{
public:
	void PrepareSoldier(int xPosition, int yPosition);
	void DrawSoldier();
	void ClearSoldier();
	void UpdateSoldierPosition(int newPosition);
	void KillSoldier();
	bool IsLanded();
	Rectangle GetCollisionRectangle();
	bool IsAlive();
	int GetPointsOnKill();
private:
	Texture2D soldierTexture;
	int xPos;
	int yPos;
	bool alive;
	Rectangle collisionRectangle;
	//const int pointsOnKill = 5;
};

#endif // !SOLDIER_H

