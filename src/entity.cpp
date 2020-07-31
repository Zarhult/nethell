#include "entity.hpp"
#include "sprite.hpp"

void Entity::setState(EntityState state)
{
    mState = state;
}

Sprite::SpriteShPtr Entity::getSprite() const
{
    return mSpritePtr;
}

EntityState Entity::getState() const
{
    return mState;
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
