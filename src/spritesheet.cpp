#include <SDL2/SDL.h>
#include "spritesheet.hpp"

int SpriteSheet::getSpriteWidth() const
{
    return this->spriteWidth;
}

int SpriteSheet::getSpriteHeight() const
{
    return this->spriteHeight;
}

int SpriteSheet::getSpritesX() const
{
    return this->spritesX;
}

int SpriteSheet::getSpritesY() const
{
    return this->spritesY;
}
