#include "AlienManager.h"

AlienManager::AlienManager()
{
}

AlienManager::~AlienManager()
{
    printf("Destroyed Alien Manager\n");
}

void AlienManager::SetupAlienPosition()
{
    Vector2 windowSize = Window::GetInstance()->GetWindowSize();
    Vector2 spriteSize = Renderer::GetInstance()->GetSizeFromTexture("assets/green.png");
    int startPosX = (windowSize.x * 0.5 - trunc(spriteSize.x * 0.5)) - ((spriteSize.x + spacing) * trunc(cols * 0.5));

    int currRow = 0;
    int currCol = 0;
    for(auto wpAlien : aliens)
    {
        if(const auto& spAlien = wpAlien.lock())
        {
            int posY = windowSize.y * (0.1 + (0.075 * currRow)) - spriteSize.y;
            int posX = startPosX + (spriteSize.x + spacing) * currCol;
            spAlien->SetPos(posX, posY);
            currCol++;

            if(currCol >= 11)
            {
                currRow++;
                currCol = 0;
            }
        }
    }
}

void AlienManager::MoveAliens(float deltaTime)
{
    Vector2f vel = bMoveRight ? Vector2f(1, 0) * Speed * deltaTime : Vector2f(-1, 0) * Speed * deltaTime;

    for(const auto& alien : aliens)
    {
        if(auto ptr = alien.lock())
        {
            ptr->SetPos(ptr->GetPos() + vel);
        }
    }
}

void AlienManager::MoveAliensDown(float deltaTime)
{
    bMoveRight = !bMoveRight;
    for(const auto& alien : aliens)
    {
        if(auto ptr = alien.lock())
        {
            ptr->SetPos(ptr->GetPos() + Vector2f(0, ptr->GetSize().y));
        }
    }
}

bool AlienManager::CheckAlienHitEdge(float deltaTime)
{
    Vector2f vel = bMoveRight ? Vector2f(1, 0) * Speed * deltaTime : Vector2f(-1, 0) * Speed * deltaTime;

    for(const auto& alien : aliens)
    {
        if(auto ptr = alien.lock())
        {
            if(ptr->IsDead())
                continue;

            SDL_FRect newRect = ptr->GetRect();
            newRect.x += vel.x;
            newRect.y += vel.y;

            if(!HelperFunction::IsWithinBounds(newRect, Window::GetInstance()->GetWindowRect()))
            {
                return true;
            }
        }
    }
    return false;
}

std::weak_ptr<Bullet> AlienManager::GetBullet()
{
    for(auto bullet : bullets)
    {
        if(auto ptr = bullet.lock())
        {
            if(!ptr->GetFired())
            {
                return bullet;
            }
        }
    }
}

int selectedCol = 0;
void AlienManager::FireBullet()
{
    int selectedCol = rand() % cols;
        
    int i = 0;
    int row = enemyPaths.size() - 1;
    Vector2f pos;
    bool bFound = false;

    /*
    *   @todo : Something wrong here
    */
    for(auto itr = aliens.begin(); itr != aliens.end(); itr++)
    {
        if(i == selectedCol + (cols * row))
        {
            if(auto ptr = itr->lock())
            {
                if(!ptr->IsDead())
                {
                    pos = ptr->GetCenter();
                    bFound = true;
                    break;
                }
                row--;
            }
        }
        
        i++;

        if(i < selectedCol)
            break;
    }
    
    if(!bFound)
        return;

    auto bullet = GetBullet();
    if(auto ptr = bullet.lock())
    {
        ptr->Fire(pos, Vector2f(0, 1), ETeam::ENEMY);
    }
}

void AlienManager::RegisterBullets(const std::list<std::weak_ptr<Bullet>> &bullets)
{
    this->bullets = bullets;
}

std::list<std::shared_ptr<Sprite>> AlienManager::CreateEnemies()
{
    std::list<std::shared_ptr<Sprite>> alienSprites;

    for (size_t row = 0; row < enemyPaths.size(); row++ )
    {
        for(size_t col = 0; col < cols; col++)
        {
            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(enemyPaths[row]);

            aliens.push_back(enemy);
            alienSprites.push_back(enemy);
        }
    }

    SetupAlienPosition();

    return alienSprites;
}

void AlienManager::Reset()
{
    for(auto wpAlien : aliens)
    {
        if(const auto& spAlien = wpAlien.lock())
        {
            spAlien->Reset();
        }
    }
    SetupAlienPosition();
}

void AlienManager::Update(float deltaTime)
{
    if(CheckAlienHitEdge(deltaTime))
        MoveAliensDown(deltaTime);
    else
        MoveAliens(deltaTime);

    //printf("%d - %d\n", SDL_GetTicks64(), lastFiredTick);
    if(SDL_GetTicks64() - lastFiredTick >= shootingInterval)
    {
        FireBullet();
        lastFiredTick = SDL_GetTicks64();
        //printf("Last Fired Tick: %d", lastFiredTick);
    }
}