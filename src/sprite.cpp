#include "sprite.hpp"
#include <SDL2/SDL.h>

void Sprite::render()
{
    int spriteWidth  {spriteSheetPtr->getSpriteWidth() };
    int spriteHeight {spriteSheetPtr->getSpriteHeight()};
    int spritesX     {spriteSheetPtr->getSpritesX()    };

    // Calculate clip area of sprite sheet to use in rendering
    SDL_Rect clip {(spriteNum % spritesX) * spriteWidth, (spriteNum / spritesX) * spriteHeight, spriteWidth, spriteHeight};

    spriteSheetPtr->render(xPos, yPos, &clip);
}

void Sprite::setXY(int x, int y)
{
    xPos = x;
    yPos = y;
}

int Sprite::getXPos() const
{
    return xPos;
}

int Sprite::getYPos() const
{
    return yPos;
}
