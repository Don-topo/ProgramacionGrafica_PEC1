#include "Helicopter.h"

void Helicopter::PrepareHelicopter(int yPosition, bool direction)
{
	yPos = yPosition;
	movingLeft = direction;
	alive = true;
	health = 2;
	if (movingLeft) {
		helicopterTexture = LoadTexture("resources/Helicopter_Left.png");
		xPos = 0 - helicopterTexture.width;
	} else {
		helicopterTexture = LoadTexture("resources/Helicopter_right.png");
		xPos = screenWidth;
	}
	collisionRectangle.x = xPos;
	collisionRectangle.y = yPos;
	collisionRectangle.width = helicopterTexture.width;
	collisionRectangle.height = helicopterTexture.height;
}

void Helicopter::DrawHelicopter()
{
	DrawTexture(helicopterTexture, xPos, yPos, WHITE);
}

void Helicopter::UpdateHelicopter()
{
	if (alive) {
		if (movingLeft) xPos++; else xPos--;
		collisionRectangle.x = xPos;
	}	
}

void Helicopter::ClearHelicopter()
{
	UnloadTexture(helicopterTexture);
}

int Helicopter::GetPosition()
{	
	return (xPos + (helicopterTexture.width / 2));
}

int Helicopter::GetTextureHeight()
{
	return helicopterTexture.height;
}

bool Helicopter::IsOutOfScreen()
{
	if (!movingLeft) {
		return ((xPos + helicopterTexture.width) < 0);
	}
	else
	{
		return ((xPos - helicopterTexture.width > screenWidth));
	}	
}

Rectangle Helicopter::GetCollisionRectangle()
{
	return collisionRectangle;
}

int Helicopter::GetPointsOnKill()
{
	return points;
}

void Helicopter::HitHelicopter()
{
	health--;
	alive = health > 0;
}

bool Helicopter::IsAlive()
{
	return alive;
}
