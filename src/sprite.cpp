#include "sprite.hpp"
#include "SDL2/SDL.h"

void Sprite::render()
{
    int spriteWidth  {mSpriteSheetPtr->getSpriteWidth() };
    int spriteHeight {mSpriteSheetPtr->getSpriteHeight()};
    int spritesX     {mSpriteSheetPtr->getSpritesX()    };

    // Calculate clip area of sprite sheet to use in rendering
    SDL_Rect clip {(mSpriteNum % spritesX) * spriteWidth, (mSpriteNum / spritesX) * spriteHeight, spriteWidth, spriteHeight};

    mSpriteSheetPtr->render(mXPos, mYPos, &clip, mAngle, nullptr, mFlipType);
}

void Sprite::shiftXY(int x, int y)
{
    mXPos += x;
    mYPos += y;
}

void Sprite::setAngle(double angle)
{
    mAngle = angle;
}

void Sprite::setFlipType(SDL_RendererFlip flipType)
{
    mFlipType = flipType;
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
    return mSpriteNum;
}

int Sprite::getXPos() const
{
    return mXPos;
}

int Sprite::getYPos() const
{
    return mYPos;
}

double Sprite::getAngle() const
{
    return mAngle;
}

SDL_RendererFlip Sprite::getFlipType() const
{
    return mFlipType;
}

bool Sprite::isOnscreen() const
{
    return mIsOnscreen;
}
