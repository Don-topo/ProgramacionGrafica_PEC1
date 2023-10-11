#include "Soldier.h"

void Soldier::PrepareSoldier(int xPosition, int yPosition)
{
	soldierTexture = LoadTexture("resources/Soldier.png");
	//soldierTexture = TextureManager::GetSoldierTexture();
	xPos = xPosition;
	yPos = yPosition;
	alive = true;
	collisionRectangle.x = xPos;
	collisionRectangle.y = yPos;
	collisionRectangle.width = soldierTexture.width;
	collisionRectangle.height = soldierTexture.height;
}

void Soldier::DrawSoldier()
{
	DrawTexture(soldierTexture, xPos, yPos, WHITE);
}

void Soldier::ClearSoldier()
{
	UnloadTexture(soldierTexture);
}

void Soldier::UpdateSoldierPosition(int newPosition)
{
	if (!IsLanded() && alive) {
		yPos -= newPosition;
		collisionRectangle.y = yPos;
	}	
}

void Soldier::KillSoldier()
{
	soldierTexture = LoadTexture("resources/Dead.png");
	alive = false;
}

bool Soldier::IsLanded()
{
	return (yPos + soldierTexture.height >= screenHeight);
}

Rectangle Soldier::GetCollisionRectangle()
{
	return collisionRectangle;
}

bool Soldier::IsAlive()
{
	return alive;
}

int Soldier::GetPointsOnKill()
{
	return 5;
}
