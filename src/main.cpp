#include "game.hpp"
#include "spriteenums.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

int main() 
{
    try
    {
        const int winWidth  {1920};
        const int winHeight {1080};

        Game game(winWidth, winHeight);

        // Cap framerate and game processing at the game's FPS
        Uint32 frameStart;
        Uint32 frameTime;
        while (game.isRunning())
        {
            frameStart = SDL_GetTicks();

            game.eventHandle();
            game.step();
            game.render();

            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < static_cast<Uint32>(game.getTimeStep()))
            {
                SDL_Delay(game.getTimeStep() - frameTime);
            }
        }
    }
    catch(std::logic_error &exception)
    {
        std::cerr << "Logic error: " << exception.what() << std::endl;
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

