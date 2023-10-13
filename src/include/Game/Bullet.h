#ifndef __BULLET_H__
#define __BULLET_H__

#include "Sprite.h"
#include "Interfaces/IDamage.h"
#include "Interfaces/ITeam.h"

class Bullet : public Sprite, public ITeam
{
protected:
    float speed = 1000.f;
    Vector2f fireDirection = Vector2f(0,0);

public:
    Bullet(std::string Name, const char* assetPath);

    void Fire(Vector2f pos, Vector2f direction, ETeam team, float speed = 0);

    virtual void Update(float deltaTime) override;
    void Move(float deltaTime);

    void OutOfBounds();

    void Reset();

    bool GetFired();

    virtual void Hit(const std::shared_ptr<Sprite>& otherSprite) override;
};

#endif // __BULLET_H__