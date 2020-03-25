#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"

int main() 
{
    try
    {
	int winWidth	    {1920};
	int winHeight	    {1080};
	int spriteWidth	    {256};
	int spriteHeight    {256};
	int spritesX	    {2};
	int spritesY	    {2};

	Game gameObj(winWidth, winHeight);
	if (gameObj.loadSpriteSheet("images/test.jpg", spriteWidth, spriteHeight, spritesX, spritesY))
	{
	    gameObj.moveSprite(0, 0, 0);
	    gameObj.moveSprite(1, spriteWidth, 0);
	    gameObj.moveSprite(2, 0, spriteHeight);
	    gameObj.moveSprite(3, spriteWidth, spriteHeight);

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

