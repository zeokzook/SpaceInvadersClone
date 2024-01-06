#include "Game.h"

Game::Game()
{
    std::cout << "Successfully Constructed Game" << std::endl;
}

Game::~Game()
{
    std::cout << "Deconstructed Game" << std::endl;
}

void Game::Init(const char* windowName, int width, int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if(TTF_Init() < 0)
    {
        printf("Failed to initialize TTF: %s\n", SDL_GetError());
    }
    
    window = Window::GetInstance()->CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height);
    if(window == NULL)
    {
        std::cout << "Failed to Create Window: " << SDL_GetError() << std::endl;
        Quit();
    }

    renderer = Renderer::GetInstance()->CreateRenderer(window);
    if(renderer == NULL)
    {
        printf("Failed to Create Renderer: %s\n", SDL_GetError());
        Quit();
    }

    CreatePlayer();
    CreateEnemies();
    CreateBullets();

    userInterface = std::make_shared<UserInterface>();

    bGameActive = true;
}

void Game::PollEvents()
{
    if(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_QUIT:
                Quit();
                break;

            case SDL_KEYDOWN:
                PlayerInputKeyDown(Event.key.keysym.sym);
                switch(Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Quit();
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                PlayerInputKeyUp(Event.key.keysym.sym);
                break;

            default:
                break;
        }
    }
}

void Game::Update(float deltaTime)
{
    if(!bGameActive)
        return;

    if(auto playerPtr = player.lock())
    {
        if(playerPtr->IsDead())
        {
            return;
        }
    }

    for(const auto& sprite : sprites)
    {
        sprite->Update(deltaTime);
    }

    alienManager->Update(deltaTime);
    
    CheckCollisions();
    CheckDeleted();
}

void Game::Render()
{
    if(!bGameActive)
        return;

    SDL_RenderClear(renderer);

    for(const auto& sprite : sprites)
    {
        sprite->Render();
    }

    userInterface->Render();

    SDL_RenderPresent(renderer);
}

void Game::CreatePlayer()
{
    auto ptrPlayer = std::make_shared<Player>("Player", "assets/player.png");
    player = ptrPlayer;
    Vector2f playerSize = ptrPlayer->GetSize();
    Vector2 windowSize = Window::GetInstance()->GetWindowSize();
    ptrPlayer->SetPos(Vector2f(windowSize.x * 0.5f - playerSize.x * 0.5f, windowSize.y * 0.9f - playerSize.y * 0.5f));
    sprites.push_back(ptrPlayer);

}

void Game::CreateEnemies()
{
    alienManager = std::make_shared<AlienManager>();

    sprites.merge(alienManager->CreateEnemies());
}

void Game::CreateBullets()
{
    std::list<std::weak_ptr<Bullet>> bullets;

    for (size_t i = 0; i < MAXBULLETCOUNT; i++)
    {
        auto ptrBullet = std::make_shared<Bullet>("Bullet " + std::to_string(i), "assets/bullet.png");
        sprites.push_back(ptrBullet);
        bullets.push_back(ptrBullet);
    }
    
    if(auto ptrPlayer = player.lock())
        ptrPlayer->SetBulletRefs(bullets);

    alienManager->RegisterBullets(bullets);
}

void Game::PlayerInputKeyDown(SDL_Keycode key)
{
    if(auto ptrPlayer = player.lock())
    {
        switch(key)
        {
            case SDLK_a:
                ptrPlayer->velocity.x = -1;
                break;
            case SDLK_d:
                ptrPlayer->velocity.x = 1;
                break;
            // case SDLK_w:
            //     ptrPlayer->velocity.y = -1;
            //     break;
            // case SDLK_s:
            //     ptrPlayer->velocity.y = 1;
            //     break;
            case SDLK_SPACE:
                ptrPlayer->Shoot();
                break;
            default:
                break;
        }
    }
}

void Game::PlayerInputKeyUp(SDL_Keycode key)
{
    if(auto ptrPlayer = player.lock())
    {
        switch(key)
        {
            case SDLK_a:
                if(ptrPlayer->velocity.x < 0)
                    ptrPlayer->velocity.x = 0;
                break;
            case SDLK_d:
                if(ptrPlayer->velocity.x > 0)
                    ptrPlayer->velocity.x = 0;
                break;
            // case SDLK_w:
            //     if(ptrPlayer->velocity.y < 0)
            //         ptrPlayer->velocity.y = 0;
            //     break;
            // case SDLK_s:
            //     if(ptrPlayer->velocity.y > 0)
            //         ptrPlayer->velocity.y = 0;
            //     break;
            case SDLK_SPACE:
                ptrPlayer->StopShoot();
                break;
            case SDLK_F1:
                DebugFunction();
                break;
            default:
                break;
        }
    }
}

void Game::CheckCollisions()
{
    for(const auto& firstSprite : sprites)
    {
        if(!firstSprite->GetCollisionEnabled() || !firstSprite->GetVisiblity())
            continue;

        for(const auto& secondSprite : sprites)
        {
            if(!secondSprite->GetCollisionEnabled() || !secondSprite->GetVisiblity())
                continue;
                
            if(firstSprite == secondSprite)
                continue;
            
            if(HelperFunction::AABB(firstSprite->GetRect(), secondSprite->GetRect()))
            {
                //printf("Hit! %s against %s\n", firstSprite->GetName().c_str(), secondSprite->GetName().c_str());
                firstSprite->Hit(secondSprite);
            }       
        }
    }
}

void Game::CheckDeleted()
{
    std::vector<std::shared_ptr<Sprite>> spritesToErase;
    for(auto itr = sprites.begin(); itr != sprites.end(); itr++)
    {
        if(itr->get()->GetMarkDelete())
        {
            spritesToErase.push_back(*itr);
        }
    }

    if(spritesToErase.size() > 0)
    {
        for(const auto& sprite : spritesToErase)
        {
            sprites.remove(sprite);
        }
    }
}

void Game::Quit()
{
    sprites.clear();
    alienManager = nullptr;

    Renderer::GetInstance()->Destroy();
    Window::GetInstance()->Destroy();

    bGameActive = false;
    userInterface = nullptr;
    TTF_Quit();
    SDL_Quit();
}

bool Game::IsGameActive()
{
    return bGameActive;
}

Sprite* randSprite;
void Game::DebugFunction()
{
    // if(randSprite)
    // {
    //     randSprite->SetCollisionEnabled(true);
    // }

    //randSprite = sprites[rand() % sprites.size()];
    // randSprite->SetCollisionEnabled(false);

    // for(auto sprite : sprites)
    // {
    //     ITeam* interface = dynamic_cast<ITeam*>(sprite);
    //     if(interface != nullptr)
    //         std::cout << interface->GetTeam() << std::endl;
    // }
    //alienManager->Reset();
}
