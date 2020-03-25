#include <SDL2/SDL.h>
#include "spritesheet.hpp"

int SpriteSheet::getSpriteWidth() const
{
    return this->mSpriteWidth;
}

int SpriteSheet::getSpriteHeight() const
{
    return this->mSpriteHeight;
}

int SpriteSheet::getSpritesX() const
{
    return this->mSpritesX;
}

int SpriteSheet::getSpritesY() const
{
    return this->mSpritesY;
}
