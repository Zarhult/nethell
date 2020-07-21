#include "entity.hpp"

void Entity::render()
{
	this->mSpritePtr->render();
}

void Entity::moveSprite(int xPos, int yPos)
{
	this->mSpritePtr->setXY(xPos, yPos);
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
