#include "sprite.hpp"
#include "SDL2/SDL.h"
#include <assert.h>

void Sprite::render()
{
    int spriteWidth  {mSpriteSheetPtr->getSpriteWidth() };
    int spriteHeight {mSpriteSheetPtr->getSpriteHeight()};
    int spritesX     {mSpriteSheetPtr->getSpritesX()    };

    // Calculate clip area of sprite sheet to use in rendering
    SDL_Rect clip {(mSpriteNum % spritesX) * spriteWidth, (mSpriteNum / spritesX) * spriteHeight, spriteWidth, spriteHeight};

    mSpriteSheetPtr->render(mXPos, mYPos, &clip);
}

void Sprite::setXY(int x, int y)
{
    mXPos = x;
    mYPos = y;
}

void Sprite::setSpriteNum(int spriteNum)
{
    mSpriteNum = spriteNum;
}

void Sprite::toggleOnscreen()
{
    if (!mIsOnscreen)
    {
        mIsOnscreen = true;
    }
    else
    {
        mIsOnscreen = false;
    }
}

int Sprite::getSpriteNum() const
{
    assert(this);

    return mSpriteNum;
}

int Sprite::getXPos() const
{
    assert(this);

    return mXPos;
}

int Sprite::getYPos() const
{
    assert(this);

    return mYPos;
}

bool Sprite::isOnscreen() const
{
    assert(this);

    return mIsOnscreen;
}
