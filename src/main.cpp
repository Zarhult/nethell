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
        Game game;

        // Avoid using accessors repeatedly
        const double timeStep {game.getTimeStep()};
        const bool debugEnabled {game.debugEnabled()};
        
        Uint32 currentTime {0}; // Time at start of game loop
        Uint32 lastFrameTime {0}; // Time at start of previous game loop
        double catchupTime {0.0}; // Amount of game time that needs to be handled each main loop, accounting for potential lag
        double cap = game.getFrameStepCap() * timeStep; // Cap for the above in case things get way behind
        
        // Now run the game, adhering to max and min FPS (by making multiple steps before rendering, when get behind)
        while (game.isRunning()) {
            currentTime = SDL_GetTicks();
            catchupTime += currentTime - lastFrameTime;
            
            if (catchupTime > cap) {
                catchupTime = cap;
            }

            while (catchupTime >= timeStep) {
                catchupTime -= timeStep;
                
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    game.eventHandle(event);
                }
                
                if (debugEnabled) {
                    std::cout << "Stepping game. catchupTime: " << catchupTime << std::endl;
                }
                
                game.step(timeStep); // Advance game logic by 1 frame worth of time
            }
            
            game.render();
            lastFrameTime = currentTime;
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

