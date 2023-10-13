#include "Enemy.h"

Enemy::Enemy(const FEnemyData& enemyData) : Sprite(enemyData.spriteName, enemyData.spritePath)
{
    SetTeam(ETeam::ENEMY);
    score = enemyData.score;
}

void Enemy::SetScore(int score)
{
    this->score = score;
}

bool Enemy::IsDead()
{
    return !GetVisiblity();
}

void Enemy::Dead()
{
    SetVisiblity(false);
}

void Enemy::Reset()
{
    SetVisiblity(true);
}

void Enemy::Update(float deltaTime)
{

}

void Enemy::Damage(ETeam team, int damage, EDamageType damageType)
{
    //printf("Dead\n");
    Dead();
}
