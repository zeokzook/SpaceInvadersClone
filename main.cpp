#include <memory>
#include "src/include/Game/Game.h"

const char* GAMENAME = "SDLTemplate";
const int WIDTH = 1000;
const int HEIGHT = 800;
const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char* argv[])
{
    std::unique_ptr<Game> game = std::make_unique<Game>();

    game->Init(GAMENAME, WIDTH, HEIGHT);

    float deltaTime = 0.f;
    while(game->IsGameActive())
    {
        Uint64 start = SDL_GetTicks64();

        game->PollEvents();
        game->Update(deltaTime/1000);
        game->Render();

        Uint64 end = SDL_GetTicks64();

        deltaTime = end - start;

        // if(elapsedTime < SCREEN_TICKS_PER_FRAME && game->IsGameActive())
        // {
        //     SDL_Delay(SCREEN_TICKS_PER_FRAME - elapsedTime);
        // }
    }

    return EXIT_SUCCESS;
}