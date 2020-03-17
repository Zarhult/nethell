#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"

int main() 
{
    Game gameObj;

    if (gameObj.init(600, 600))
    {
	if (gameObj.loadTexture("images/test.jpg"))
	{
	    while (gameObj.getRunStatus())
	    {
		gameObj.eventHandle();
		gameObj.render();
	    }
	}
    }

    gameObj.clean();

    return 0;
}

