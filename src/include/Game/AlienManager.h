#ifndef __ALIENMANAGER_H__
#define __ALIENMANAGER_H__

#include "Bullet.h"
#include "Enemy.h"
#include "Window.h"
#include <list>

class AlienManager
{
private:
    std::list<std::weak_ptr<Enemy>> aliens;
    std::list<std::weak_ptr<Bullet>> bullets;

    float Speed = 100.f;
    bool bMoveRight = true;

    int cols = 11;
    int spacing = 15;

    std::vector<FEnemyData> enemyPaths = { 
        FEnemyData(EEnemyType::RED),
        FEnemyData(EEnemyType::YELLOW),
        FEnemyData(EEnemyType::YELLOW),
        FEnemyData(EEnemyType::GREEN),
        FEnemyData(EEnemyType::GREEN)
    };

    int shootingInterval = 1000;
    Uint64 lastFiredTick = 0;

public:
    AlienManager();
    ~AlienManager();

protected:
    void SetupAlienPosition();

    void MoveAliens(float deltaTime);
    void MoveAliensDown(float deltaTime);
    bool CheckAlienHitEdge(float deltaTime);

    std::weak_ptr<Bullet> GetBullet();

    void FireBullet();
public:
    std::list<std::shared_ptr<Sprite>> CreateEnemies();

    void Reset();

    void Update(float deltaTime);

    void RegisterBullets(const std::list<std::weak_ptr<Bullet>>& bullets);
};

#endif // __ALIENMANAGER_H__