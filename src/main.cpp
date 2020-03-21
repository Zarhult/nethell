#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"

int main() 
{
    try
    {
	Game gameObj(1920, 1080);

	if (gameObj.loadTexture("images/test.jpg", 0, 0))
	{
	    while (gameObj.getRunStatus())
	    {
		gameObj.eventHandle();
		gameObj.render();
	    }
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

    IMG_Quit();
    SDL_Quit();

    return 0;
}

