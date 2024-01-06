#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "AlienManager.h"
#include "Renderer.h"
#include "Window.h"
#include "HelperFunctions.h"
#include "UserInterface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int MAXBULLETCOUNT = 25;

class Game
{
protected:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event Event;
    bool bGameActive = false;

    std::shared_ptr<AlienManager> alienManager;

    std::list<std::shared_ptr<Sprite>> sprites;

    std::weak_ptr<Player> player;

    std::shared_ptr<UserInterface> userInterface;

public:
    Game();
    ~Game();

    void Init(const char *windowName, int width, int height);

    void PollEvents();
    void Update(float deltaTime);
    void Render();

    void CreatePlayer();
    void CreateEnemies();
    void CreateBullets();

    void PlayerInputKeyDown(SDL_Keycode key);
    void PlayerInputKeyUp(SDL_Keycode key);

    void CheckCollisions();
    void CheckDeleted();

    void Quit();

    bool IsGameActive();

    void DebugFunction();
};

#endif // __GAME_H__