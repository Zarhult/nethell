#include "entity.hpp"
#include <assert.h>

void Entity::render()
{
    assert(this);

    this->mSpritePtr->render();
}

void Entity::moveSprite(int xPos, int yPos)
{
    assert(this);

    this->mSpritePtr->setXY(xPos, yPos);
}

void Entity::changeSprite(int newSpriteNum)
{
    assert(this);

    this->mSpritePtr->setSpriteNum(newSpriteNum);
}

void Entity::toggleSprite()
{
    assert(this);

    this->mSpritePtr->toggleOnscreen();

}

int Entity::getSpriteNum() const
{
    assert(this);

    return this->mSpritePtr->getSpriteNum();
}

int Entity::getSpriteXPos() const
{
    assert(this);

    return this->mSpritePtr->getXPos();
}

int Entity::getSpriteYPos() const
{
    assert(this);

    return this->mSpritePtr->getYPos();
}

int Entity::isOnscreen() const
{
    assert(this);

    return this->mSpritePtr->isOnscreen();
}

int Entity::getMaxHP() const
{
    assert(this);

    return this->maxHP;
}

int Entity::getHP() const
{
    assert(this);

    return this->HP;
}
