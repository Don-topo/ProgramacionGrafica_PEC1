#ifndef PLAYER_H
#define PLAYER_H


#include "raylib.h"
#include "GlobalGameDefines.h"

class Player
{
public:
	void PreparePlayer();
	void DrawPlayer();
	void ClearPlayer();
	void MovePlayer();	
	void SetCannonRotation(float newRotation);
	float GetCannonRotation();
	Rectangle GetDestination();
	Vector2 GetShootPosition();
	Vector2 GetCannonDimensions();
private:
	Texture2D playerBase;
	Texture2D playerCannon;
	int BaseXPosition;
	int BaseYPosition;
	int cannonXPosition;
	int cannonYPosition;
	float cannonScale;
	Rectangle cannonOriginRectangle;
	Rectangle cannonDestRectangle;
	Vector2 playerCannonV;
	float cannonRotation;
	// Shoot
	bool isShooting;	
	Vector2 shootPosition;
};

#endif // !PLAYER_H