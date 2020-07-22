#include "entity.hpp"
#include "sprite.hpp"

Sprite::SpriteShPtr Entity::getSprite() const
{
    return this->mSpritePtr;
}

void Entity::setState(EntityState state)
{
    mState = state;
}

int Entity::getMaxHP() const
{
    return this->maxHP;
}

int Entity::getHP() const
{
    return this->HP;
}
