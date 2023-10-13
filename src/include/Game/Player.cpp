#include "Player.h"

Player::Player(std::string playerName, const char *assetPath) : Sprite(playerName, assetPath)
{
    Team = ETeam::PLAYER;
}


Player::~Player()
{
    
}

void Player::SetBulletRefs(const std::list<std::weak_ptr<Bullet>> &bullets)
{
    this->bullets = bullets;
}

std::weak_ptr<Bullet> Player::GetBullet()
{
    for(const auto& ptrBullet : bullets)
    {
        if(auto bullet = ptrBullet.lock())
        {
            if(!bullet->GetFired())
            {
                return ptrBullet;
            }
        }
    }

    return std::weak_ptr<Bullet>();
}

void Player::Update(float deltaTime)
{
    Move(deltaTime);
    ProcessFire();
}

void Player::Move(float deltaTime)
{
    Vector2 windowSize = Window::GetInstance()->GetWindowSize();
    float newX = GetPos().x + velocity.x * speed * deltaTime;
    float newY = GetPos().y + velocity.y * speed * deltaTime;
    Vector2f newPos = Vector2f(SDL_clamp(newX, 0, windowSize.x - GetSize().x), SDL_clamp(newY, 0, windowSize.y - GetSize().y));
    SetPos(newPos);
}

void Player::ProcessFire()
{
    if(bShooting)
    {
        if(ONLYONEBULLET)
            FireOnce();
        else
            Fire();
    }
}

void Player::Shoot()
{
    bShooting = true;
}

void Player::StopShoot()
{
    bShooting = false;
}

void Player::Fire()
{
    if(SDL_GetTicks64() >= lastFired + (1000 / fireRate))
    {
        auto foundBullet = GetBullet();
        if(auto ptr = foundBullet.lock())
        {
            ptr->Fire(GetCenter(), Vector2f(0, -1), GetTeam());
            lastFired = SDL_GetTicks64();
        }
    }
}

void Player::FireOnce()
{
    bool bShouldShoot = false;
    if(auto firedBulletPtr = firedBullet.lock())
    {
        if(!firedBulletPtr->GetFired())
        {
            bShouldShoot = true;
        }
    }
    else
    {
        bShouldShoot = true;
    }

    if(bShouldShoot)
    {
        firedBullet = GetBullet();
        if(auto newBullet = firedBullet.lock())
        {
            newBullet->Fire(GetCenter(), Vector2f(0, -1), GetTeam());
        }
    }
}

float Player::GetSpeed()
{
    return speed;
}

void Player::SetSpeed(float speed)
{
    this->speed = speed;
}

bool Player::IsDead()
{
    return bDead;
}

Uint32 Callback(Uint32 interval, void* param)
{
    static_cast<Player*>(param)->Respawn();

    return 0;
}

void Player::Dead()
{
    bDead = true;
    SetVisiblity(false);

    SDL_AddTimer(3000, Callback, this);
}

void Player::Respawn()
{
    bDead = false;
    SetVisiblity(true);
}

void Player::Damage(ETeam team, int damage, EDamageType damageType)
{
    Dead();
}