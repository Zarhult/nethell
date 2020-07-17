#include "spritesheet.hpp"
#include "SDL2/SDL.h"
#include <assert.h>

bool SpriteSheet::isAnimation() const
{
    assert(this);

    return this->mIsAnimation;
}

int SpriteSheet::getSpriteWidth() const
{
    assert(this);

    return this->mSpriteWidth;
}

int SpriteSheet::getSpriteHeight() const
{
    assert(this);

    return this->mSpriteHeight;
}

int SpriteSheet::getSpritesX() const
{
    assert(this);

    return this->mSpritesX;
}

int SpriteSheet::getSpritesY() const
{
    assert(this);

    return this->mSpritesY;
}
