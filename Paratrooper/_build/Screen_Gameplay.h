#ifndef SCREEN_GAMEPLAY_H
#define SCREEN_GAMEPLAY_H

#include "raylib.h"
#include "Player.h"
#include "Helicopter.h"
#include "Soldier.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "raymath.h"

struct Shoot
{
	Vector2 position;
	int radius;
	bool active;
	Vector2 velocity;
};

class Screen_Gameplay
{
public:
	void InitGameplayScreen(void);
	void UpdateGameplayScreen(void);
	void DrawGameplayScreen(void);
	void UnloadGameplayScreen(void);
	int FinishGameplayScreen(void);		
private:
	void GetCounters();
	const char* scoreText = "SCORE:";
	const int xScoreText = 25;
	const char* landedText = "LANDED:";
	const int xLandedText = screenWidth / 2 - 50;
	const char* timeText = "TIME:";
	const int xTimeText = screenWidth - 175;
	int finishScreen;
	char numberstring[(sizeof(int) * CHAR_BIT)];
	char numberstring2[(sizeof(int) * CHAR_BIT)];
	char numberstring3[(sizeof(int) * CHAR_BIT)];
	Player player{};
	GameManager gameManager{};
	EnemyManager enemyManager{};
	// Helicopter spawn
	const int helicopterSpawnInterval[3] = { 2, 3, 4 };
	int timeFromLastHelicopterSpawn;
	int currentHelicopterSpawn;
	void SetNextHelicopterSpawn();
	void CheckHelicopterSpanw();
	// Soldier spawn
	const int soldierSpanwInterval[2] = { 3, 4 };
	int timeFromLastSoldierSpawn;
	int currentSoldierSpawn;
	void SetNextSoldierSpawn();
	void CheckSoldierSpawn();
	// ball
	int xBallPosition = screenWidth / 2.f;
	int yBallPosition = screenHeight -150 / 4.f;
	float ballRadius = 2.f;
	bool ballActive = false;
	Vector2 ballDirection = { 4.f, 4.f };
	int ballSpeedX;
	int ballSpeedY;
	std::list<Shoot> shoots;
	void AddShoot();
	void CheckCollisions();
	void UpdateShootsPositions();
	void DeleteShootsOutOfScreen();
	void DrawShoots();
	Sound shootMusic;
	Sound deadMusic;
	Sound explostionMusic;
	Music backgroundMusic;
};

#endif // !SCREEN_GAMEPLAY_H