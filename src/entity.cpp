#include "entity.hpp"

void Entity::render()
{
    this->mSpritePtr->render();
}

void Entity::shiftSprite(int xPos, int yPos)
{
    this->mSpritePtr->shiftXY(xPos, yPos);
}

void Entity::setSpriteAngle(double angle)
{
    this->mSpritePtr->setAngle(angle);
}

void Entity::setSpriteFlipType(SDL_RendererFlip flipType)
{
    this->mSpritePtr->setFlipType(flipType);
}

void Entity::changeSprite(int newSpriteNum)
{
    this->mSpritePtr->setSpriteNum(newSpriteNum);
}

void Entity::toggleSprite()
{
    this->mSpritePtr->toggleOnscreen();
}

int Entity::getSpriteNum() const
{
    return this->mSpritePtr->getSpriteNum();
}

int Entity::getSpriteXPos() const
{
    return this->mSpritePtr->getXPos();
}

int Entity::getSpriteYPos() const
{
    return this->mSpritePtr->getYPos();
}

int Entity::isOnscreen() const
{
    return this->mSpritePtr->isOnscreen();
}

int Entity::getMaxHP() const
{
    return this->maxHP;
}

int Entity::getHP() const
{
    return this->HP;
}
