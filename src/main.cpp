#include "game.hpp"

int main() 
{
    Game gameObj;

    if (gameObj.init(1920, 1080))
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

