#include "entity.hpp"
#include <assert.h>

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
