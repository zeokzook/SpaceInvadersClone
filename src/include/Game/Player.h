#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Sprite.h"
#include "Bullet.h"
#include "Interfaces/ITeam.h"
#include <list>

const bool ONLYONEBULLET = true;

class Player : public Sprite, public ITeam, public IDamage
{
private:
    float speed = 200.f;

    /// @brief bullets per second
    unsigned int fireRate = 5;
    Uint64 lastFired = 0;

    std::list<std::weak_ptr<Bullet>> bullets;

    std::weak_ptr<Bullet> firedBullet;

    bool bShooting = false;

    bool bDead = false;

public:
    Vector2f velocity = Vector2f(0,0);
    
public:
    Player(std::string playerName, const char* assetPath);
    ~Player();

    void SetBulletRefs(const std::list<std::weak_ptr<Bullet>>& bullets);
    std::weak_ptr<Bullet> GetBullet();

    virtual void Update(float deltaTime) override;

    void Move(float deltaTime);
    void ProcessFire();

    void Shoot();
    void StopShoot();

    void Fire();
    void FireOnce();

    float GetSpeed();
    void SetSpeed(float speed);

    bool IsDead();
    void Dead();
    void Respawn();

    virtual void Damage(ETeam team, int damage, EDamageType damageType = EDamageType::DEFAULT) override;
};

#endif // __PLAYER_H__