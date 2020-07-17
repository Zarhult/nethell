#include "game.hpp"
#include "spriteenums.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

// TODO: wrapper around font that closes itself when out of scope (remove function from Game destructor after)

int main() 
{
    try
    {
        const int winWidth      {1920};
        const int winHeight     {1080};

        Game gameObj(winWidth, winHeight);
        gameObj.loadSpriteSheet("sprites/wizard.png", true, 120, 120, 2, 1);
        gameObj.newEntity(PLAYER, PLAYER_IDLE);
        gameObj.getEntity(0)->toggleSprite();
        gameObj.getEntity(0)->moveSprite(0, 0);

        while (gameObj.getRunStatus())
        {
            gameObj.eventHandle();
            gameObj.render();

            SDL_Delay(100);
        }
    }
    catch(std::runtime_error &exception)
    {
        std::cerr << "Runtime error: " << exception.what() << std::endl;
    }
    catch(std::exception &exception)
    {
        std::cerr << "Standard exception: " << exception.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An uncaught exception occurred." << std::endl;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

