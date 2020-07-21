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
		const int winWidth		{1920};
		const int winHeight		{1080};

		Game gameObj(winWidth, winHeight);
		gameObj.loadSpriteSheet("sprites/wizard.png", true, 120, 120, 2, 1);
		gameObj.newEntity(PLAYER, PLAYER_IDLE);
		gameObj.getEntity(0)->toggleSprite();
		gameObj.getEntity(0)->moveSprite(0, 0);

		gameObj.setNextFrame(SDL_GetTicks());
		while (gameObj.isRunning())
		{
			Uint32 now {SDL_GetTicks()};
			int limit {10}; // Max steps per render

			// Assuming vsync is on, so no need to delay
			while (gameObj.getNextFrame() <= now && (limit--))
			{
				gameObj.eventHandle();
				gameObj.setNextFrame(gameObj.getNextFrame() + gameObj.getFrameStep());
			}

			gameObj.render();
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

	return 0;
}

