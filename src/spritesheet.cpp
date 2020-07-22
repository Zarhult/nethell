#include "spritesheet.hpp"
#include "SDL2/SDL.h"

bool SpriteSheet::isAnimation() const
{
    return mIsAnimation;
}

int SpriteSheet::getSpriteWidth() const
{
    return mSpriteWidth;
}

int SpriteSheet::getSpriteHeight() const
{
    return mSpriteHeight;
}

int SpriteSheet::getSpritesX() const
{
    return mSpritesX;
}

int SpriteSheet::getSpritesY() const
{
    return mSpritesY;
}
