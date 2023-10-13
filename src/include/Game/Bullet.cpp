#include "Bullet.h"

Bullet::Bullet(std::string Name, const char *assetPath) : Sprite(Name, assetPath)
{
    SetVisiblity(false);
}

void Bullet::Fire(Vector2f pos, Vector2f direction, ETeam team, float speed)
{
    if(speed != 0)
        this->speed = speed;

    SetPos(pos - (GetSize() * 0.5f));
    SetTeam(team);
    fireDirection = direction;
    SetVisiblity(true);
}

void Bullet::Update(float deltaTime)
{
    Move(deltaTime);
}

void Bullet::Move(float deltaTime)
{
    if(!GetFired())
        return;
    
    Vector2f newPos = GetPos() + (fireDirection * (speed * deltaTime));
    SDL_FRect newDestRect = destRect;
    newDestRect.x = newPos.x;
    newDestRect.y = newPos.y;

    //printf("(%f,%f) + (%f,%f) * (%f * %f)) = x:%f y:%f\n", GetPos().x, GetPos().y, fireDirection.x, fireDirection.y, speed, deltaTime, newPos.x, newPos.y);

    if(!HelperFunction::IsWithinBounds(newDestRect, Window::GetInstance()->GetWindowRect()))
    {
        OutOfBounds();
        return;
        //printf("%s : Out of Bounds", GetName().c_str());
    }

    SetPos(newPos);
}

void Bullet::OutOfBounds()
{
    Reset();
}

void Bullet::Reset()
{
    SetVisiblity(false);
    fireDirection = Vector2f(0,0);
    SetTeam(ETeam::NONE);
}

bool Bullet::GetFired()
{
    return GetVisiblity();
}

void Bullet::Hit(const std::shared_ptr<Sprite> &otherSprite)
{
    if(auto teamInterface = dynamic_cast<ITeam*>(otherSprite.get()))
    {
        //printf("Other Has Team Interface\n");
        //std::cout << "My Team:" << GetTeam() << " Other Team: " << teamInterface->GetTeam() << std::endl;
        if(GetTeam() != teamInterface->GetTeam())
        {
            //printf("Different Team\n");
            if(auto damageInterface = dynamic_cast<IDamage*>(otherSprite.get()))
            {
                //printf("Damaged\n");
                damageInterface->Damage(teamInterface->GetTeam(), 1);
            }
            Reset();
        }
    }
}
