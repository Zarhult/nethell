#include "game.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

int main() 
{
    try
    {
	int winWidth	    {1920};
	int winHeight	    {1080};
	int spriteWidth	    {120};
	int spriteHeight    {120};
	int spritesX	    {2};
	int spritesY	    {1};

	Game gameObj(winWidth, winHeight);
	if (gameObj.loadSpriteSheet("sprites/wizard.png", spriteWidth, spriteHeight, spritesX, spritesY))
	{
	    gameObj.toggleSprite(PLAYER);
	    gameObj.moveSprite(PLAYER, 0, 0);

	    while (gameObj.getRunStatus())
	    {
		gameObj.eventHandle();
		gameObj.render();
		if (gameObj.getSpriteNum(PLAYER) == PLAYER_WALK)
		{
		    gameObj.changeSprite(PLAYER, PLAYER_IDLE);
		}
		else
		{
		    gameObj.changeSprite(PLAYER, PLAYER_WALK);
		}

		SDL_Delay(100);
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

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

