#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "raylib.h"
#include "GlobalGameDefines.h"

class Helicopter
{
public:
	void PrepareHelicopter(int yPosition, bool direction);
	void DrawHelicopter();
	void UpdateHelicopter();
	void ClearHelicopter();
	int GetPosition();
	int GetTextureHeight();
	bool IsOutOfScreen();
	Rectangle GetCollisionRectangle();
	int GetPointsOnKill();
	void HitHelicopter();
	bool IsAlive();
private:
	Texture2D helicopterTexture;
	int xPos;
	int yPos;
	bool movingLeft;
	Rectangle collisionRectangle;
	bool alive;
	int health;
	int points = 5;
};

#endif // !HELICOPTER_H

