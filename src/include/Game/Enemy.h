#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "FEnemyTypes.h"
#include "Sprite.h"
#include "Interfaces/IDamage.h"
#include "Interfaces/ITeam.h"

class Enemy : public Sprite, public ITeam, public IDamage
{
protected:
    int score = 0;
public:
    Enemy(const FEnemyData& enemyData);

    void SetScore(int score);

    bool IsDead();
    void Dead();
    void Reset();

    virtual void Update(float deltaTime) override;

    virtual void Damage(ETeam team, int damage, EDamageType damageType = EDamageType::DEFAULT) override;
};

#endif // __ENEMY_H__