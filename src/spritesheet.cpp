#include "spritesheet.hpp"
#include "SDL2/SDL.h"

bool SpriteSheet::isAnimation() const
{
	return this->mIsAnimation;
}

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
