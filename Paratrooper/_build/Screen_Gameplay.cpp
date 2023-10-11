#include "Screen_Gameplay.h"

void Screen_Gameplay::InitGameplayScreen(void)
{
    player.PreparePlayer();    
    backgroundMusic = LoadMusicStream("resources/Background.wav");
    backgroundMusic.looping = true;    
    SetMusicVolume(backgroundMusic, 1.f);
    PlayMusicStream(backgroundMusic);
    shootMusic = LoadSound("resources/shot.wav");
    deadMusic = LoadSound("resources/SoldierDead.wav");
    explostionMusic = LoadSound("resources/HelicopterDead.wav");
    gameManager.PrepareGameManager();
    finishScreen = 0;
    shoots.clear();
    enemyManager.ClearEnemies();
}

void Screen_Gameplay::UpdateGameplayScreen(void)
{
    // Player movement
    if (IsKeyDown(KEY_A)) {
        if (player.GetCannonRotation() > -87) player.SetCannonRotation(-1);
    }
    if (IsKeyDown(KEY_D)) {
        if (player.GetCannonRotation() < 87) player.SetCannonRotation(1);
    }  
    // Shoot
    if (IsKeyPressed(KEY_SPACE)) { 
        gameManager.Shoot();
        AddShoot();
        PlaySound(shootMusic);
    }

    UpdateShootsPositions();

    timeFromLastHelicopterSpawn++;
    timeFromLastSoldierSpawn++;
    CheckHelicopterSpanw();
    CheckSoldierSpawn();
    enemyManager.ClearOutOfScreenHelicopters();
    enemyManager.UpdateEnemies();       
    gameManager.UpdateTimePlayed();
    gameManager.UpdateLandedSoldiers(enemyManager.GetLandedSoldiers());
    // Collisions
    CheckCollisions();
    DeleteShootsOutOfScreen();
    GetCounters();
    finishScreen = gameManager.GameIsOver();
    UpdateMusicStream(backgroundMusic);
}

void Screen_Gameplay::DrawGameplayScreen(void)
{
    // Draw enemies
    enemyManager.DrawEnemies();
    DrawShoots();
    player.DrawPlayer();      
    //Draw UI
    DrawText(scoreText, xScoreText, 0, 24, WHITE);
    DrawText(numberstring, xScoreText + 100, 0, 24, PURPLE);
    DrawText(landedText, xLandedText, 0, 24, WHITE);
    DrawText(numberstring2, xLandedText + 115, 0, 24, PURPLE);
    DrawText(timeText, xTimeText, 0, 24, WHITE);
    DrawText(numberstring3, xTimeText + 85, 0, 24, PURPLE);    
}

void Screen_Gameplay::UnloadGameplayScreen(void)
{
    // UnloadTextures
    player.ClearPlayer();
    enemyManager.ClearEnemies();
    // Unload sounds
    UnloadMusicStream(backgroundMusic);
    UnloadSound(deadMusic);
    UnloadSound(explostionMusic);
    UnloadSound(shootMusic);
}

int Screen_Gameplay::FinishGameplayScreen(void)
{
    return finishScreen;
}

void Screen_Gameplay::AddShoot()
{
    Shoot newShoot{};
    newShoot.position = { player.GetDestination().x + sin(player.GetCannonRotation() * DEG2RAD),  player.GetDestination().y - cos(player.GetCannonRotation() * DEG2RAD) };
    newShoot.active = true;
    newShoot.velocity = { 3 * sin(player.GetCannonRotation() * DEG2RAD) , 3 * cos(player.GetCannonRotation() * DEG2RAD) };
    newShoot.radius = 2.f;
    shoots.push_back(newShoot);
}

void Screen_Gameplay::CheckCollisions()
{
    // Soldiers
    std::list<Soldier> soldiers = enemyManager.GetSoldiers();
    std::list<Soldier>::iterator itSoldier;
    // Helicopters
    std::list<Helicopter> helicopters = enemyManager.GetHelicopters();
    std::list<Helicopter>::iterator itHelicopter;
    // Shoots
    std::list<Shoot>::iterator itShoot;

    for (itShoot = shoots.begin(); itShoot != shoots.end(); itShoot++) {
        for (itSoldier = soldiers.begin(); itSoldier != soldiers.end(); itSoldier++) {
            if (itSoldier->IsAlive()) {
                if (CheckCollisionCircleRec(itShoot->position, itShoot->radius, itSoldier->GetCollisionRectangle())) {
                    itSoldier->KillSoldier();
                    gameManager.UpdateScore(itSoldier->GetPointsOnKill());                    
                    // delete ball
                    if (itShoot == shoots.begin()) shoots.erase(itShoot); else shoots.erase(itShoot--);
                    PlaySound(deadMusic);
                    enemyManager.UpdateSoldiersList(soldiers);
                    enemyManager.UpdateHelicoptersList(helicopters);
                    if (shoots.size() == 0) return;
                    return;
                }
            }
            if (soldiers.size() == 0) break;
        }
        if (shoots.size() > 0) {
            for (itHelicopter = helicopters.begin(); itHelicopter != helicopters.end(); itHelicopter++) {
                if (CheckCollisionCircleRec(itShoot->position, itShoot->radius, itHelicopter->GetCollisionRectangle())) {
                    itHelicopter->HitHelicopter();
                    if (!itHelicopter->IsAlive()) {
                        gameManager.UpdateScore(itHelicopter->GetPointsOnKill());
                        itHelicopter->ClearHelicopter();
                        PlaySound(explostionMusic);
                        if (itHelicopter == helicopters.begin()) helicopters.erase(itHelicopter); else helicopters.erase(itHelicopter--);
                    }
                    // delete ball
                    if (itShoot == shoots.begin()) shoots.erase(itShoot); else shoots.erase(itShoot--);
                    enemyManager.UpdateSoldiersList(soldiers);
                    enemyManager.UpdateHelicoptersList(helicopters);
                    if (shoots.size() == 0) return;
                    return;
                }
                if (helicopters.size() == 0) break;
            }
        }        
        enemyManager.UpdateSoldiersList(soldiers);
        enemyManager.UpdateHelicoptersList(helicopters);
        if (shoots.size() == 0) return;
    }
}

void Screen_Gameplay::UpdateShootsPositions()
{
    std::list<Shoot>::iterator it;
    for (it = shoots.begin(); it != shoots.end(); it++) {
        if (it->active) {
            it->position.x += it->velocity.x;
            it->position.y -= it->velocity.y;
        }        
    }    
}

void Screen_Gameplay::DeleteShootsOutOfScreen()
{
    std::list<Shoot>::iterator it;
    for (it = shoots.begin(); it != shoots.end(); it++) {
        if (it->position.x > screenWidth || it->position.x < 0 ||it-> position.y < 0) {
            if (shoots.begin() == it) shoots.erase(it); else shoots.erase(it--);
            return;
        }
    }
}

void Screen_Gameplay::DrawShoots()
{
    std::list<Shoot>::iterator it;
    for (it = shoots.begin(); it != shoots.end(); it++) {
        if (it-> active) {
            DrawCircle(it->position.x, it->position.y, it->radius, WHITE);
        }
    }
}

void Screen_Gameplay::GetCounters()
{
    int timePlayed = gameManager.GetTimePlayed() / framesPerSecond;
    sprintf(numberstring, "%d", gameManager.GetScore());
    sprintf(numberstring2, "%d", gameManager.GetLandedSoldiers());
    sprintf(numberstring3, "%02d:%02d", timePlayed % 3600 / 60, timePlayed % 60);
}

void Screen_Gameplay::SetNextHelicopterSpawn()
{    
    timeFromLastHelicopterSpawn = 0;
    currentHelicopterSpawn = helicopterSpawnInterval[GetRandomValue(0, 3)];
}

void Screen_Gameplay::CheckHelicopterSpanw()
{
    if (timeFromLastHelicopterSpawn / framesPerSecond >= currentHelicopterSpawn) {
        enemyManager.SpawnHelicopter();
        SetNextHelicopterSpawn();
    }
}

void Screen_Gameplay::SetNextSoldierSpawn()
{
    timeFromLastSoldierSpawn = 0;
    currentSoldierSpawn = soldierSpanwInterval[GetRandomValue(0, 1)];
}

void Screen_Gameplay::CheckSoldierSpawn()
{
    if (timeFromLastSoldierSpawn / framesPerSecond >= currentSoldierSpawn) {
        enemyManager.SpawnSoldier();
        SetNextSoldierSpawn();
    }
}
