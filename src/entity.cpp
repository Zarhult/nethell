#include "entity.hpp"
#include "sprite.hpp"

Sprite::SpriteShPtr Entity::getSprite() const
{
    return mSpritePtr;
}

void Entity::setState(EntityState state)
{
    mState = state;
}

double Entity::getSpeed() const
{
    return mSpeed;
}

int Entity::getMaxHP() const
{
    return mMaxHP;
}

int Entity::getHP() const
{
    return mHP;
}
