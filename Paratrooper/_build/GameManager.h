#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H


class GameManager
{
public:
	GameManager();
	void PrepareGameManager();
	bool GameIsOver();
	void UpdateScore(int value);
	void UpdateLandedSoldiers(int landed);
	void UpdateTimePlayed();
	void Shoot();
	int GetTimePlayed();
	int GetLandedSoldiers();
	int GetScore();
private:
	int landedSoldiers;
	int score;
	int timePlayed;
};

#endif // !GAME_MANAGER_H