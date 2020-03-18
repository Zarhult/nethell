#include "game.hpp"

// efficiency/practice notes: 
// 1. pass by const reference when can. 
// 2. for arguments that are consumed, define move constructor and move them. 
// 3. const after class function names when applicable.
// 4. exception handling.
// 5. verify smart pointers aren't null before use

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

