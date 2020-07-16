#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "sprite.hpp"
#include <memory>

class Entity
{
    public:
        using EntityShPtr = std::shared_ptr<Entity>;

    public:
        Entity(Sprite::SpriteShPtr spritePtr) : mSpritePtr(spritePtr) {};

        int getMaxHP() const;
        int getHP()    const;

    private:
        Sprite::SpriteShPtr mSpritePtr {nullptr}; // Pointer to entity's sprite
        int maxHP; // Add stats here...
        int HP;
};

#endif
